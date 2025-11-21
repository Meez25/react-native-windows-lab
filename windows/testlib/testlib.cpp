#include "pch.h"
#include <winrt/Windows.System.Profile.h>
#include "testlib.h"
#include <winuser.h>
#include <winrt/Windows.Security.Credentials.h>
#include <winrt/Windows.Storage.h>
#include <ShlObj.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.Globalization.h>

using namespace winrt;
using namespace winrt::Windows::Security::Credentials;
using namespace winrt::Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Foundation;
using namespace Windows::Globalization;


std::wstring StringToWideString(const std::string& str);
std::string WideStringToString(const std::wstring& wstr);

namespace winrt::testlib
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

void Testlib::Initialize(React::ReactContext const &reactContext) noexcept {
  m_context = reactContext;
}

winrt::hstring Testlib::getComputerName() noexcept {
  WCHAR buffer[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD size = sizeof(buffer) / sizeof(buffer[0]);

  if (GetComputerNameW(buffer, &size)) {
    return winrt::hstring(buffer);
  }

  return winrt::hstring(L"");
}

// Méthode asynchrone qui fait le travail
static winrt::Windows::Foundation::IAsyncAction GetOSVersionAsync(
  winrt::Microsoft::ReactNative::ReactPromise<winrt::hstring> promise) noexcept
{
  auto capturedPromise = promise;

  auto keys = single_threaded_vector<hstring>();
  keys.Append(L"OSVersionFull");

  auto props = co_await Windows::System::Profile::AnalyticsInfo::GetSystemPropertiesAsync(keys.GetView());

  if (props.HasKey(L"OSVersionFull")) {
    capturedPromise.Resolve(props.Lookup(L"OSVersionFull"));
  }
  else {
    capturedPromise.Resolve(L"Version inconnue");
  }
}

bool Testlib::setToClipBoard(winrt::hstring text) noexcept {
  try {
    // Ouvrir le presse-papiers avec nullptr (équivalent NULL en C++/WinRT)
    if (!OpenClipboard(nullptr)) {
      OutputDebugStringW(L"Erreur: Impossible d'ouvrir le clipboard\n");
      return false;
    }

    // Vider le presse-papiers
    EmptyClipboard();

    // Convertir hstring en wstring
    std::wstring wstr(text);
    size_t cch = wstr.length();

    // Allouer la mémoire globale
    HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (cch + 1) * sizeof(WCHAR));
    if (hglbCopy == NULL) {
      OutputDebugStringW(L"Erreur: Allocation mémoire échouée\n");
      CloseClipboard();
      return false;
    }

    // Verrouiller le handle et copier le texte
    LPWSTR lptstrCopy = (LPWSTR)GlobalLock(hglbCopy);
    if (lptstrCopy == NULL) {
      OutputDebugStringW(L"Erreur: GlobalLock échoué\n");
      GlobalFree(hglbCopy);
      CloseClipboard();
      return false;
    }

    memcpy(lptstrCopy, wstr.c_str(), cch * sizeof(WCHAR));
    lptstrCopy[cch] = (WCHAR)0; // caractère null
    GlobalUnlock(hglbCopy);

    // Placer le handle dans le presse-papiers
    if (SetClipboardData(CF_UNICODETEXT, hglbCopy) == NULL) {
      OutputDebugStringW(L"Erreur: SetClipboardData échoué\n");
      GlobalFree(hglbCopy);
      return false;
    }

    // Fermer le presse-papiers
    CloseClipboard();

    OutputDebugStringW(L"Texte copié dans le clipboard avec succès\n");
    return true;
  }
  catch (...) {
    OutputDebugStringW(L"Exception dans setToClipBoard\n");
    CloseClipboard();
    return false;
  }
}

void Testlib::getOSVersion(winrt::Microsoft::ReactNative::ReactPromise<winrt::hstring> promise) noexcept
{
  auto asyncOp = GetOSVersionAsync(promise);
  asyncOp.Completed([promise](auto action, auto status)
    {
      if (status == winrt::Windows::Foundation::AsyncStatus::Error)
      {
        std::stringstream errorCode;
        errorCode << "0x" << std::hex << action.ErrorCode() << std::endl;

        auto error = winrt::Microsoft::ReactNative::ReactError();
        error.Message = "HRESULT " + errorCode.str() + ": " + std::system_category().message(action.ErrorCode());
        promise.Reject(error);
      }
    });
}

void Testlib::setGenericPassword(
  std::string service,
  std::string username,
  std::string password,
  React::ReactPromise<bool>&& result) noexcept {

  try {
    // Validation
    if (service.empty() || username.empty() || password.empty()) {
      result.Reject("Service, username and password cannot be empty");
      return;
    }

    std::wstring wservice = StringToWideString(service);
    std::wstring wusername = StringToWideString(username);
    std::wstring wpassword = StringToWideString(password);

    PasswordVault vault;

    // Supprimer les credentials existants pour ce service/username
    try {
      auto existing = vault.FindAllByResource(wservice);
      for (auto&& cred : existing) {
        if (cred.UserName() == wusername) {
          vault.Remove(cred);
          OutputDebugStringW(L"Removed existing credential\n");
        }
      }
    }
    catch (const winrt::hresult_error& ex) {
      // 0x80070490 = Element not found (normal si aucun credential existe)
      if (ex.code() != static_cast<winrt::hresult>(0x80070490)) {
        // C'est une autre erreur, on la relance
        throw;
      }
      // Sinon on continue, c'est normal
      OutputDebugStringW(L"No existing credentials found (normal)\n");
    }

    // Ajouter le nouveau credential
    PasswordCredential cred(wservice, wusername, wpassword);
    vault.Add(cred);

    OutputDebugStringW(L"Credential added successfully\n");
    result.Resolve(true);

  }
  catch (const winrt::hresult_error& ex) {
    std::wstringstream ss;
    ss << L"PasswordVault error: 0x" << std::hex << ex.code()
      << L" - " << ex.message().c_str();
    OutputDebugStringW(ss.str().c_str());

    result.Reject("Failed to save password");
  }
  catch (const std::exception& ex) {
    OutputDebugStringW(L"Standard exception in setGenericPassword\n");
    result.Reject(ex.what());
  }
  catch (...) {
    OutputDebugStringW(L"Unknown error in setGenericPassword\n");
    result.Reject("Unknown error");
  }
}

int Testlib::getBatteryLife() noexcept {

  SYSTEM_POWER_STATUS system_power_status;
  if (!GetSystemPowerStatus(&system_power_status)) {
    // Erreur lors de l'appel à l'API Windows
    return -1;  // Ou une valeur d'erreur appropriée
  }
  
  return system_power_status.BatteryLifePercent;
}

void Testlib::writeToFile(
  std::string filename,
  std::string filecontent,
  React::ReactPromise<bool>&& result) noexcept {

  // Récupérer le chemin du bureau
  char desktopPath[MAX_PATH];
  HRESULT hr = SHGetFolderPathA(
    nullptr,
    CSIDL_DESKTOPDIRECTORY,
    nullptr,
    0,
    desktopPath);

  if (FAILED(hr)) {
    result.Reject("Failed to get desktop path");
    return;
  }

  // Construire le chemin complet : Bureau\filename
  std::string fullPath = std::string(desktopPath) + "\\" + filename;

  HANDLE hFile = CreateFileA(
    fullPath.c_str(),
    GENERIC_WRITE,
    0,
    nullptr,
    CREATE_ALWAYS,
    FILE_ATTRIBUTE_NORMAL,
    nullptr);

  if (hFile == INVALID_HANDLE_VALUE) {
    result.Reject("Failed to create or open file");
    return;
  }

  DWORD bytesWritten = 0;
  BOOL writeResult = WriteFile(
    hFile,
    filecontent.c_str(),
    static_cast<DWORD>(filecontent.length()),
    &bytesWritten,
    nullptr);

  CloseHandle(hFile);

  if (writeResult && bytesWritten == filecontent.length()) {
    result.Resolve(true);
  }
  else {
    result.Reject("Failed to write all data to file");
  }
}

void Testlib::getGenericPassword(
  std::string service,
  winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValueObject> promise) noexcept
{
  auto capturedPromise = promise;
  try {
    std::wstring wservice = StringToWideString(service);

    std::wstringstream debugMsg;
    debugMsg << L"Getting password for service: " << wservice << L"\n";
    OutputDebugStringW(debugMsg.str().c_str());

    PasswordVault vault;
    auto resultObject = winrt::Microsoft::ReactNative::JSValueObject();

    IVectorView<PasswordCredential> credentials{ nullptr };

    try {
      credentials = vault.FindAllByResource(wservice);
      std::wstringstream ss;
      ss << L"FindAllByResource found " << credentials.Size() << L" credential(s)\n";
      OutputDebugStringW(ss.str().c_str());
    }
    catch (const winrt::hresult_error& e) {
      // 0x80070490 = Element not found (normal si vault vide ou service inexistant)
      if (e.code() == static_cast<winrt::hresult>(0x80070490)) {
        OutputDebugStringW(L"No credentials found for this service (normal)\n");
        resultObject["username"] = "";
        resultObject["password"] = "";
        capturedPromise.Resolve(resultObject);
        return;
      }

      // Autre erreur, on la relance
      std::wstringstream ss;
      ss << L"FindAllByResource failed with unexpected error: 0x" << std::hex << e.code() << L"\n";
      OutputDebugStringW(ss.str().c_str());
      throw;
    }

    // Vérifier si on a des credentials
    if (!credentials || credentials.Size() == 0) {
      OutputDebugStringW(L"No credentials found, returning empty\n");
      resultObject["username"] = "";
      resultObject["password"] = "";
      capturedPromise.Resolve(resultObject);
      return;
    }

    try {
      PasswordCredential cred = credentials.GetAt(0);
      OutputDebugStringW(L"Retrieved credential, calling RetrievePassword()\n");

      cred.RetrievePassword();
      OutputDebugStringW(L"Password retrieved successfully\n");

      std::string username = WideStringToString(std::wstring(cred.UserName()));
      std::string password = WideStringToString(std::wstring(cred.Password()));

      std::wstringstream ss;
      ss << L"Username length: " << username.length() << L", Password length: " << password.length() << L"\n";
      OutputDebugStringW(ss.str().c_str());

      resultObject["username"] = username;
      resultObject["password"] = password;

      capturedPromise.Resolve(resultObject);
      OutputDebugStringW(L"Promise resolved successfully\n");
    }
    catch (const winrt::hresult_error& e) {
      std::wstringstream ss;
      ss << L"Error retrieving password: 0x" << std::hex << e.code() << L" - " << e.message().c_str() << L"\n";
      OutputDebugStringW(ss.str().c_str());
      capturedPromise.Reject("Error retrieving password");
      return;
    }
  }
  catch (const winrt::hresult_error& e) {
    std::wstringstream ss;
    ss << L"WinRT exception: 0x" << std::hex << e.code() << L" - " << e.message().c_str() << L"\n";
    OutputDebugStringW(ss.str().c_str());
    capturedPromise.Reject("WinRT error");
  }
  catch (const std::exception& e) {
    OutputDebugStringW(L"Standard exception in getGenericPassword\n");
    capturedPromise.Reject(e.what());
  }
  catch (...) {
    OutputDebugStringW(L"Unknown error in getGenericPassword\n");
    capturedPromise.Reject("Unknown error in getGenericPassword");
  }
}

void Testlib::resetGenericPassword(
  std::string service,
  React::ReactPromise<bool>&& result) noexcept {

  try {
    std::wstring wservice = StringToWideString(service);

    std::wstringstream ss;
    ss << L"Resetting credentials for service: " << wservice << L"\n";
    OutputDebugStringW(ss.str().c_str());

    PasswordVault vault;
    IVectorView<PasswordCredential> credentials{ nullptr };

    try {
      credentials = vault.FindAllByResource(wservice);

      std::wstringstream foundMsg;
      foundMsg << L"Found " << credentials.Size() << L" credential(s) to remove\n";
      OutputDebugStringW(foundMsg.str().c_str());

      // Supprimer tous les credentials pour ce service
      for (uint32_t i = 0; i < credentials.Size(); ++i) {
        auto cred = credentials.GetAt(i);
        vault.Remove(cred);

        std::wstringstream removedMsg;
        removedMsg << L"Removed credential #" << (i + 1) << L"\n";
        OutputDebugStringW(removedMsg.str().c_str());
      }

      OutputDebugStringW(L"All credentials removed successfully\n");
      result.Resolve(true);
    }
    catch (const winrt::hresult_error& e) {
      // 0x80070490 = Element not found (pas de credentials à supprimer)
      if (e.code() == static_cast<winrt::hresult>(0x80070490)) {
        OutputDebugStringW(L"No credentials found to remove (normal)\n");
        result.Resolve(true);
        return;
      }
      // Autre erreur, on la relance
      throw;
    }
  }
  catch (const winrt::hresult_error& ex) {
    std::wstringstream ss;
    ss << L"HRESULT error in reset: 0x" << std::hex << ex.code() << L" - " << ex.message().c_str() << L"\n";
    OutputDebugStringW(ss.str().c_str());
    result.Reject("Error in resetGenericPassword");
  }
  catch (const std::exception& ex) {
    OutputDebugStringW(L"Standard exception in resetGenericPassword\n");
    result.Reject(ex.what());
  }
  catch (...) {
    OutputDebugStringW(L"Unknown error in resetGenericPassword\n");
    result.Reject("Unknown error in resetGenericPassword");
  }
}

void Testlib::deleteKeychainEntriesWithPrefix(
  std::string prefix,
  React::ReactPromise<void>&& result) noexcept {

 

  try {
    std::wstring wprefix = StringToWideString(prefix);

    PasswordVault vault;
    auto allCredentials = vault.RetrieveAll();

    
    std::vector<PasswordCredential> toDelete;
    for (auto const& cred : allCredentials) {
      std::wstring resource(cred.Resource());
      if (resource.find(wprefix) == 0) {
        toDelete.push_back(cred);
      }
    }

   
    for (auto const& cred : toDelete) {
      vault.Remove(cred);
    }

    result.Resolve();
  }
  catch (const winrt::hresult_error& ex) {
    std::wstringstream ss;
    ss << L"HRESULT error: 0x" << std::hex << ex.code();
    
    result.Reject("Error in deleteKeychainEntriesWithPrefix");
  }
  catch (const std::exception& ex) {
    
    result.Reject(ex.what());
  }

  
}

void Testlib::showAlert(
  std::string title,
  std::string message,
  React::ReactPromise<void>&& result) noexcept
{
  try {
    std::wstring wTitle = StringToWideString(title);
    std::wstring wMessage = StringToWideString(message);

    std::thread([wTitle, wMessage, result = std::move(result)]() mutable {
      try {
        // MessageBox avec uniquement un bouton OK
        MessageBoxW(
          nullptr,
          wMessage.c_str(),
          wTitle.c_str(),
          MB_OK |                     // Seulement le bouton OK
          MB_ICONINFORMATION |        // Icône information
          MB_SETFOREGROUND |          // Mettre au premier plan
          MB_TASKMODAL                // Modal pour l'application
        );

        // Toujours résoudre car il n'y a qu'un bouton OK
        result.Resolve();
      }
      catch (...) {
        result.Reject("Dialog error");
      }
      }).detach();
  }
  catch (...) {
    result.Reject("Failed to show alert");
  }
}

void Testlib::showConfirm(std::string title, std::string message, React::ReactPromise<bool>&& result) noexcept {
  try {
    // Capturer les paramètres
    std::wstring wTitle = StringToWideString(title);
    std::wstring wMessage = StringToWideString(message);

    // Lancer sur un thread séparé pour ne pas bloquer
    std::thread([wTitle, wMessage, result = std::move(result)]() mutable {
      try {
        // MessageBox standard Windows - fonctionne toujours
        int response = MessageBoxW(
          nullptr,                    // Pas de fenêtre parente
          wMessage.c_str(),           // Message
          wTitle.c_str(),             // Titre
          MB_OKCANCEL |               // Boutons OK et Cancel
          MB_ICONQUESTION |           // Icône question
          MB_SETFOREGROUND |          // Mettre au premier plan
          MB_TASKMODAL                // Modal pour l'application
        );

        // IDOK = 1, IDCANCEL = 2
        result.Resolve(response == IDOK);
      }
      catch (...) {
        result.Reject("Dialog error");
      }
      }).detach();
  }
  catch (...) {
    result.Reject("Failed to show dialog");
  }
}

} // namespace winrt::testlib




std::wstring StringToWideString(const std::string& str) {
  if (str.empty()) return std::wstring();
  int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
  std::wstring wstrTo(sizeNeeded, 0);
  MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], sizeNeeded);
  return wstrTo;
}

std::string WideStringToString(const std::wstring& wstr) {
  if (wstr.empty()) return std::string();
  int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
  std::string strTo(sizeNeeded, 0);
  WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], sizeNeeded, NULL, NULL);
  return strTo;
}

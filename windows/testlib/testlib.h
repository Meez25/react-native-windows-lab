#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeTestlibDataTypes.g.h")
  #include "codegen/NativeTestlibDataTypes.g.h"
#endif
#include "codegen/NativeTestlibSpec.g.h"

#include "NativeModules.h"

namespace winrt::testlib
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

REACT_MODULE(Testlib)
struct Testlib
{
  /*using ModuleSpec = testlibCodegen::TestlibSpec;*/

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(getComputerName)
    winrt::hstring getComputerName() noexcept;

  REACT_SYNC_METHOD(setToClipBoard)
    bool setToClipBoard(winrt::hstring) noexcept;

  REACT_METHOD(getOSVersion)
    void getOSVersion(winrt::Microsoft::ReactNative::ReactPromise<winrt::hstring> promise) noexcept;

  REACT_METHOD(setGenericPassword)
    void setGenericPassword(
      std::string service,
      std::string username,
      std::string password,
      React::ReactPromise<bool>&& result) noexcept;

  REACT_METHOD(getGenericPassword)
    void getGenericPassword(
      std::string service,
      winrt::Microsoft::ReactNative::ReactPromise<winrt::Microsoft::ReactNative::JSValueObject> promise) noexcept;

  REACT_METHOD(resetGenericPassword)
    void resetGenericPassword(
      std::string service,
      React::ReactPromise<bool>&& result) noexcept;

  REACT_METHOD(deleteKeychainEntriesWithPrefix)
    void deleteKeychainEntriesWithPrefix(
      std::string prefix,
      React::ReactPromise<void>&& result) noexcept;

  REACT_SYNC_METHOD(getBatteryLife)
    int getBatteryLife() noexcept;

  REACT_METHOD(writeToFile)
    void writeToFile(std::string filename, std::string filecontent, React::ReactPromise<bool>&& result) noexcept;

  REACT_METHOD(showConfirm)
    void showConfirm(std::string title, std::string message, React::ReactPromise<bool>&& result) noexcept;

  REACT_METHOD(showAlert)
    void showAlert(std::string title, std::string message, React::ReactPromise<void>&& result) noexcept;


  private:
    React::ReactContext m_context;
};

} // namespace winrt::testlib

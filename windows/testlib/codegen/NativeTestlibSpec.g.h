
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once
// clang-format off

// #include "NativeTestlibDataTypes.g.h" before this file to use the generated type definition
#include <NativeModules.h>
#include <tuple>

namespace testlibCodegen {

inline winrt::Microsoft::ReactNative::FieldMap GetStructInfo(TestlibSpec_getGenericPassword_returnType*) noexcept {
    winrt::Microsoft::ReactNative::FieldMap fieldMap {
        {L"username", &TestlibSpec_getGenericPassword_returnType::username},
        {L"password", &TestlibSpec_getGenericPassword_returnType::password},
    };
    return fieldMap;
}

struct TestlibSpec : winrt::Microsoft::ReactNative::TurboModuleSpec {
  static constexpr auto methods = std::tuple{
      SyncMethod<std::string() noexcept>{0, L"getComputerName"},
      SyncMethod<std::string() noexcept>{1, L"getOSVersion"},
      SyncMethod<bool(std::string) noexcept>{2, L"setToClipBoard"},
      Method<void(std::string, std::string, std::string, Promise<bool>) noexcept>{3, L"setGenericPassword"},
      Method<void(std::string, Promise<TestlibSpec_getGenericPassword_returnType>) noexcept>{4, L"getGenericPassword"},
      Method<void(std::string, Promise<bool>) noexcept>{5, L"resetGenericPassword"},
      Method<void(std::string, Promise<void>) noexcept>{6, L"deleteKeychainEntriesWithPrefix"},
      SyncMethod<double() noexcept>{7, L"getBatteryLife"},
      Method<void(std::string, std::string, Promise<bool>) noexcept>{8, L"writeToFile"},
      Method<void(std::string, std::string, Promise<void>) noexcept>{9, L"showAlert"},
      Method<void(std::string, std::string, Promise<bool>) noexcept>{10, L"showConfirm"},
      Method<void(Promise<std::string>) noexcept>{11, L"showDatePicker"},
  };

  template <class TModule>
  static constexpr void ValidateModule() noexcept {
    constexpr auto methodCheckResults = CheckMethods<TModule, TestlibSpec>();

    REACT_SHOW_METHOD_SPEC_ERRORS(
          0,
          "getComputerName",
          "    REACT_SYNC_METHOD(getComputerName) std::string getComputerName() noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(getComputerName) static std::string getComputerName() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          1,
          "getOSVersion",
          "    REACT_SYNC_METHOD(getOSVersion) std::string getOSVersion() noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(getOSVersion) static std::string getOSVersion() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          2,
          "setToClipBoard",
          "    REACT_SYNC_METHOD(setToClipBoard) bool setToClipBoard(std::string value) noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(setToClipBoard) static bool setToClipBoard(std::string value) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          3,
          "setGenericPassword",
          "    REACT_METHOD(setGenericPassword) void setGenericPassword(std::string service, std::string username, std::string password, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(setGenericPassword) static void setGenericPassword(std::string service, std::string username, std::string password, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          4,
          "getGenericPassword",
          "    REACT_METHOD(getGenericPassword) void getGenericPassword(std::string service, ::React::ReactPromise<TestlibSpec_getGenericPassword_returnType> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(getGenericPassword) static void getGenericPassword(std::string service, ::React::ReactPromise<TestlibSpec_getGenericPassword_returnType> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          5,
          "resetGenericPassword",
          "    REACT_METHOD(resetGenericPassword) void resetGenericPassword(std::string service, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(resetGenericPassword) static void resetGenericPassword(std::string service, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          6,
          "deleteKeychainEntriesWithPrefix",
          "    REACT_METHOD(deleteKeychainEntriesWithPrefix) void deleteKeychainEntriesWithPrefix(std::string prefix, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(deleteKeychainEntriesWithPrefix) static void deleteKeychainEntriesWithPrefix(std::string prefix, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          7,
          "getBatteryLife",
          "    REACT_SYNC_METHOD(getBatteryLife) double getBatteryLife() noexcept { /* implementation */ }\n"
          "    REACT_SYNC_METHOD(getBatteryLife) static double getBatteryLife() noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          8,
          "writeToFile",
          "    REACT_METHOD(writeToFile) void writeToFile(std::string filename, std::string filecontent, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(writeToFile) static void writeToFile(std::string filename, std::string filecontent, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          9,
          "showAlert",
          "    REACT_METHOD(showAlert) void showAlert(std::string title, std::string message, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(showAlert) static void showAlert(std::string title, std::string message, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          10,
          "showConfirm",
          "    REACT_METHOD(showConfirm) void showConfirm(std::string title, std::string message, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(showConfirm) static void showConfirm(std::string title, std::string message, ::React::ReactPromise<bool> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          11,
          "showDatePicker",
          "    REACT_METHOD(showDatePicker) void showDatePicker(::React::ReactPromise<std::string> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(showDatePicker) static void showDatePicker(::React::ReactPromise<std::string> &&result) noexcept { /* implementation */ }\n");
  }
};

} // namespace testlibCodegen

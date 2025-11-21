# testlib - React Native Windows Module

A React Native Windows module created using `react-native-windows` and following the official native platform development guide.

## Overview

This library was created to explore and demonstrate React Native Windows native module development. It contains several custom functions that bridge JavaScript/TypeScript code with native Windows C++ implementations.

## Development Setup

### Prerequisites

Before working with this library, ensure you have:
- All React Native for Windows development dependencies installed
- Visual Studio 2022 (or 2019) with the following workloads:
  - **Desktop development with C++**
  - **Universal Windows Platform development**
- Node.js and Yarn

For complete setup instructions, refer to the [React Native for Windows environment setup guide](https://microsoft.github.io/react-native-windows/docs/rnw-dependencies).

## Project Creation

This library was initialized using the following commands:

```bat
npx --yes create-react-native-library@0.48.9 --react-native-version ^0.80.0 testlib
cd testlib
yarn add react-native-windows@^0.80.0 --dev
yarn add react-native-windows@* --peer
yarn install
npx react-native init-windows --template cpp-lib --overwrite
```

## Key Files for Module Development

When adding or modifying native functionality, you'll primarily work with these **4 core files**:

### 1. `windows/testlib/testlib.h`
- **Purpose**: C++ header file containing function declarations and class definitions
- **What to do**: Declare your native methods and their signatures here

### 2. `windows/testlib/testlib.cpp`
- **Purpose**: C++ implementation file containing the actual native code logic
- **What to do**: Implement the native functionality that will be exposed to JavaScript

### 3. `src/NativeTestlib.ts`
- **Purpose**: TypeScript specification file defining the native module interface
- **What to do**: Define the TypeScript types and method signatures that match your native implementations

### 4. `src/index.tsx`
- **Purpose**: Main export file that exposes the module's API to consumers
- **What to do**: Export the functions and types you want to make available to users of the library

## Testing Your Changes

To test the module during development:

1. Navigate to the example app directory:
   ```bat
   cd example
   ```

2. Run the Windows example app:
   ```bat
   yarn react-native run-windows
   ```

   Or from the library root:
   ```bat
   yarn example react-native run-windows
   ```

## Visual Studio Usage

When modifying the native Windows code, you can open the Visual Studio solution for a better development experience:

1. Navigate to `windows/testlib.sln` and open it in Visual Studio
2. Make changes to the `.h` and `.cpp` files
3. Build the solution in Visual Studio to check for compilation errors
4. The changes will be reflected when you run the example app

**Tip**: Visual Studio provides IntelliSense, debugging capabilities, and easier navigation through the C++ codebase.

## Development Workflow

1. **Define the API**: Start by defining your function signatures in `src/NativeTestlib.ts`
2. **Declare in C++**: Add corresponding declarations in `windows/testlib/testlib.h`
3. **Implement in C++**: Write the native implementation in `windows/testlib/testlib.cpp`
4. **Export the API**: Export your functions in `src/index.tsx`
5. **Test**: Run the example app to verify functionality

## Repository Structure

```
testlib/
├── src/                      # TypeScript/JavaScript source
│   ├── NativeTestlib.ts     # Native module interface definition
│   └── index.tsx            # Main export file
├── windows/                  # Windows native code
│   └── testlib/
│       ├── testlib.h        # C++ header file
│       ├── testlib.cpp      # C++ implementation
│       └── testlib.sln      # Visual Studio solution
├── example/                  # Example app for testing
└── android/, ios/           # Other platform implementations
```

## Additional Resources

- [React Native for Windows Documentation](https://microsoft.github.io/react-native-windows/)
- [Native Modules Guide](https://microsoft.github.io/react-native-windows/docs/native-modules)
- [Turbo Modules Documentation](https://reactnative.dev/docs/the-new-architecture/pillars-turbomodules)

---

**Note**: This library uses the Turbo Module architecture with C++ implementation for Windows, Kotlin for Android, and Objective-C for iOS.

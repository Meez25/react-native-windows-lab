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

1. **Start the Metro bundler**: Navigate to the example app directory and start the bundler:
   ```bat
   cd example
   yarn start
   ```

2. **Run from Visual Studio**: Open `example/windows/<ExampleAppName>.sln` in Visual Studio and run the project directly from there using the **Play** button or **F5**

**Tip**: This workflow allows you to debug both JavaScript (via Metro) and native C++ code (via Visual Studio) simultaneously.

## Visual Studio Usage

When modifying the native Windows code:

1. **Open the library solution**: Navigate to `windows/testlib.sln` and open it in Visual Studio to edit the native module code
2. **Make changes**: Edit the `.h` and `.cpp` files in the `windows/testlib/` directory
3. **Test in the example app**: Open `example/windows/<ExampleAppName>.sln` in Visual Studio to run and debug the example app with your changes
4. **Build and run**: Press F5 or click the Play button to build and launch the app

**Visual Studio provides**:
- IntelliSense for code completion
- Breakpoint debugging for C++ code
- Easy navigation through the codebase
- Immediate feedback on compilation errors

## Development Workflow

1. **Define the API**: Start by defining your function signatures in `src/NativeTestlib.ts`
2. **Declare in C++**: Add corresponding declarations in `windows/testlib/testlib.h`
3. **Implement in C++**: Write the native implementation in `windows/testlib/testlib.cpp`
4. **Export the API**: Export your functions in `src/index.tsx`
5. **Test**:
   - Run `yarn start` in the `example/` folder
   - Open and run the project from `example/windows/` in Visual Studio

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
│       └── testlib.sln      # Visual Studio solution (library)
├── example/                  # Example app for testing
│   └── windows/             # Visual Studio solution (example app)
└── android/, ios/           # Other platform implementations
```

## Additional Resources

- [React Native for Windows Documentation](https://microsoft.github.io/react-native-windows/)
- [Native Modules Guide](https://microsoft.github.io/react-native-windows/docs/native-modules)
- [Turbo Modules Documentation](https://reactnative.dev/docs/the-new-architecture/pillars-turbomodules)

---

**Note**: This library uses the Turbo Module architecture with C++ implementation for Windows, Kotlin for Android, and Objective-C for iOS.

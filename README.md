# Setup Guide

This guide will walk you through setting up the different labs project on your machine using Conan for dependency management and CMake for building the project.

## Prerequisites

Before you begin, make sure you have the following installed on your machine:

- **Python** (required for Conan)
- **Conan** (C/C++ package manager)
- **CMake** (build system)
- **Compiler** (GCC, Clang, MSVC, etc.)

## Step-by-Step Setup

### 1. Install Conan

Conan is a package manager for C/C++ that will help us manage our dependencies. You can install Conan using `pip`:

```sh
pip install conan
```

### 2. Clone the Repository

Clone the `Raylib-Labs` repository to your local machine:

```sh
git clone https://github.com/Farzoo/Raylib-Labs.git
cd Raylib-Labs
```

### 3. Build the Project

After installing the dependencies, configure and build the project :

#### Using Command Line

Set up the environment for building with Conan integration:

```sh
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="./conan_provider.cmake" -B "./cmake-build"
cmake --build "./cmake-build"
```

#### Or Using an IDE (Visual Studio or CLion)

##### Visual Studio

1. **Open Visual Studio**.
2. **Open Project/Solution** and navigate to the project directory.
3. **Open CMake Project** (select `CMakeLists.txt`).
4. **Configure Project**: It should automatically detect the configuration.
5. **Build**: Use the built-in commands.

##### CLion

1. **Open CLion**.
2. **Open Project** and navigate to the project directory.
3. CLion automatically detects `CMakeLists.txt`or load it manually.
4. **Configure Project**: It should automatically handle configurations for all subprojects.
5. **Build**: Use the built-in commands for individual subprojects.

### 5. Run the Projects

After building, run the executables from your build directories. Here’s how:

#### Using Command Line

Navigate to your build directory and run the appropriate executable:

##### On Windows
```sh
cd cmake-build/<project-directory>
./<project_executable>.exe
```

##### On macOS and Linux
```sh
cd cmake-build/<project-directory>
./<project_executable>
```

#### Using an IDE

Run the project directly from the IDE interface.

##### Visual Studio

1. After configuration, select the subproject you wish to run.
2. Use the "Start" button or `F5` to run the selected subproject.

##### CLion

1. After configuration, select the subproject you wish to run and click "Run" or press `Shift+F10`.

## Additional Notes

- Check your compiler and CMake versions if you encounter build issues.
- For more details on configurations, consult the [Conan documentation](https://docs.conan.io/2/) and [CMake documentation](https://cmake.org/documentation/).
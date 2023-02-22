# Claw.js

**A hardware accelerated linear algebra library.** 

> **Warning**
>
> Claw.js is currently in very early development. It's not going to solve any of your problems yet, but I'm working on it regularly.


## Requirements

- [CMake](https://cmake.org/) >= 3.1
- [Ninja](https://ninja-build.org/) >= 1.0

### Linux

You can install the requirements from your package manager,
using apt:
```sh
$ sudo apt-get install cmake ninja
```

pacman:
```sh
$ sudo pacman -S cmake ninja
```


### MacOS

You can install the requirements from [Homebrew](https://brew.sh/):

```sh
$ brew install cmake ninja
```

### Windows

You can either download the installer available for CMake or use a package manager like chocolately:
```ps
> choco install cmake ninja
```

## Installation

This will install the npm package and then run the install script that compiles the CMake project from source automatically.

```sh
$ npx claw-js@latest
```
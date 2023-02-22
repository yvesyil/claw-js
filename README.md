# Claw.js

**A hardware accelerated linear algebra library for JavaScript.**

> **Warning**
> 
> Claw.js is currently in very early development. It's not going to solve any of your problems yet, but I'm working on it regularly.

> **Note**
> This README is dedicated to the core C library (libclaw). See the [claw-js npm package](https://www.npmjs.com/package/claw-js) to learn about the JavaScript interface.


## About

There are many libraries for Python for numerical computation, especially for linear algebra e.g. Numpy, PyTorch. Not many options are available for Node.js and to be fair, JavaScript is not the most suitable programming language for the job. But like many people from the JS community, I told myself, why not?

Claw.js uses [OpenCL](https://www.khronos.org/opencl/). I know that it's not the latest and greatest API for GPUs. The reason I wanted to first develop with that is portability. I don't want Claw.js to be dependent on a specific hardware vendor, you should be able to use it with any GPU you have!

However, support for [CUDA](https://developer.nvidia.com/cuda-zone) will come in the near future.

### Stack

- Language: C11
- Build tool: [CMake](https://cmake.org/)
- Device (GPU) API: [OpenCL](https://www.khronos.org/opencl/)
- Testing: [Unity](https://github.com/ThrowTheSwitch/Unity) for C, [Jest](https://jestjs.io/) for JS.

## Goals

> **Note**
> Items with higher importance are usually appears higher in the list, so it's essentially a priority queue.

- [x] First implementations of core library (datatypes, interfaces).
- [ ] Implement primitive matrix operations using OpenCL.
- [ ] Create bindings for Node.js (instead of using [FFI](https://www.npmjs.com/package/ffi-napi)).
- [ ] Support for CUDA.
- [ ] SIMD optimizations.
- [ ] Bindings for other runtimes e.g. [Deno](https://deno.land/).

## Installation

> **Note**
> This README is dedicated to the core C library (libclaw). If you would like to use it with JavaScript, see the README at [claw-js in npm](https://www.npmjs.com/package/claw-js).

### Requirements

- [CMake](https://cmake.org/) >= 3.1
- [Ninja](https://ninja-build.org/) >= 1.0

### Build the shared object file from source (Mac & Linux)

1. Clone this repo: `git clone https://github.com/tussoftwaredesign/claw-js.git`
2. Navigate to the project root: `cd claw-js`
3. Make a build directory: `mkdir build`
4. Generate the build file: `cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release`
5. Compile: `cmake --build build -j10`
6. The compiled `libclaw.so` (`libclaw.dylib` on Mac) shared object (dynamic link library) file will be inside `build`

## Documentation

> **Note**
> This README is dedicated to the core C library (libclaw). If you would like to see the documentation for JavaScript, see the README at [claw-js in npm](https://www.npmjs.com/package/claw-js).

### Basic Example of the C API

```c
#include <stdio.h>

#include <claw.h>

int main(int argc, char **argv)
{
    // initialize the library
    claw_init(); 
    
    // define three matrices a, b, and c.
    struct claw_mat a;
    struct claw_mat b;
    struct claw_mat c;
    
    // initialize a and b with random values between 0 and 1 and give the shape 1024x1024.
    claw_create_matrix_rand_unit(&a, 1024, 1024, CLAW_FLT32);
    claw_create_matrix_rand_unit(&b, 1024, 1024, CLAW_FLT32);
    
    // print a and b
    claw_print_matrix(stdout, &a);
    claw_print_matrix(stdout, &b);
   
    // c = a * b
    claw_matmul(&a, &b, &c);
    
    // print c 
    claw_print_matrix(stdout, &c);
    
    // cleanup
    claw_free(a);
    claw_free(b);
    claw_free(c);
}
```

## Contributing

Please contact [@yvesyil](https://github.com/yvesyil) before making any changes.

## License

[MIT License](./LICENSE)

## Acknowledgments

- Developer: Yiğit Yılmaz [@yvesyil](https://github.com/yvesyil)
- Project supervisor: John Barrett [@jcbtus](https://github.com/jcbtus)

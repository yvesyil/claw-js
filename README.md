# Claw.js

**A hardware accelerated linear algebra library for JavaScript.**

> **Warning**
> 
> Claw.js is currently in very early development. It's not going to solve any of your problems yet, but I'm working on it regularly.

## About

There are many libraries for Python for numerical computation, especially for linear algebra e.g. Numpy, PyTorch. Not many options are available for Node.js and to be fair, JavaScript is not the most suitable programming language for the job. But like many people from the JS community, I told myself, why not?

Claw.js uses [OpenCL](https://www.khronos.org/opencl/). I know that it's not the latest and greatest API for GPUs. The reason I wanted to first develop with that is portability. I don't want Claw.js to be dependent on a specific hardware vendor, you should be able to use it with any GPU you have!

However, support for [CUDA](https://developer.nvidia.com/cuda-zone) will come in the near future.

### Stack

- Language: C99
- Build tool: [CMake](https://cmake.org/)
- Device (GPU) API: [OpenCL](https://www.khronos.org/opencl/)
- Testing: [Unity](https://github.com/ThrowTheSwitch/Unity) for C, [Jest](https://jestjs.io/) for JS.

<!--
## Installation

## Usage

## Documentation
-->

## Goals

> **Note**
> Items with higher importance are usually appears higher in the list, so it's essentially a priority queue.

- [x] First implementations of core library (datatypes, interfaces).
- [ ] Implement primitive matrix operations using OpenCL.
- [ ] Create bindings for Node.js (instead of using [FFI](https://www.npmjs.com/package/ffi-napi)).
- [ ] Support for CUDA.
- [ ] SIMD optimizations.
- [ ] Bindings for other runtimes e.g. [Deno](https://deno.land/).

<!--
## Contributing

## License
-->

## Acknowledgments

- Developer: Yiğit Yılmaz [@yvesyil](https://github.com/yvesyil)
- Project supervisor: John Barrett [@jcbtus](https://github.com/jcbtus)
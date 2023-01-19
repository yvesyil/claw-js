# Claw.js

**A hardware accelerated linear algebra library for JavaScript.**

## About

There are many libraries for Python for numerical computation, especially for linear algebra e.g. Numpy, PyTorch. Not that many exist for Node.js and to be fair, JavaScript is not the most suitable programming language for the job. But like many people from the JS community, I told myself, why not?

Claw.js uses [OpenCL](https://www.khronos.org/opencl/). Yes, yes I know that it's not the fastest GPGPU API. The reason I wanted to use that is portability. I don't want Claw.js to be dependent on a specific hardware manufacturer, you should be able to use it with any GPU you have!

However, support for [CUDA](https://developer.nvidia.com/cuda-zone) will come in the near future.

### Stack

- Language: C99
- Build tool: [CMake](https://cmake.org/)
- Device (GPU) API: [OpenCL](https://www.khronos.org/opencl/)
- Testing: [Unity](https://github.com/ThrowTheSwitch/Unity)

<!--
## Installation

## Usage

## Documentation
-->

## Goals

- [x] First implementations of core library (datatypes, interfaces).
- [ ] Implement primitive matrix operations using OpenCL.
- [ ] Create bindings for Node.js.
- [ ] Support for CUDA.
- [ ] SIMD optimizations.

<!--
## Contributing

## License

## Contact
-->

## Acknowledgments

- Developer: Yiğit Yılmaz [@yvesyil](https://github.com/yvesyil)
- Project supervisor: John Barrett [@jcbtus](https://github.com/jcbtus)
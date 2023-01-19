Intel(R) Core(TM) i5-8257U CPU @ 1.40GHz supports OpenCL 1.2
Device Intel(R) Iris(TM) Plus Graphics 645 supports OpenCL 1.2
[](https://stackoverflow.com/questions/7892955/how-can-i-test-for-opencl-compatibility)

[I've tested OpenCL on macbook air 2011, which has a Core i5-2467M. And i can tell you that OpenCL implementation made by apple, DOES not work properly on CPU, just on GPU. The big problem is when you set a workgroup size greater than 1.](https://stackoverflow.com/a/8101151/20729952)

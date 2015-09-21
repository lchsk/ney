## Build status


| [Linux][lin-link] | [Coveralls][cov-link] |
| :---------------: | :-------------------: |
| ![lin-badge]      | ![cov-badge]          |

[lin-badge]: https://travis-ci.org/lchsk/ney.png?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/lchsk/ney "Travis build status"
[cov-badge]: https://coveralls.io/repos/lchsk/ney/badge.png?branch=master
[cov-link]:  https://coveralls.io/r/lchsk/ney?branch=master


## How to Download
1. Download source code with git by using a command:
`git clone https://github.com/lchsk/ney.git --recursive`

(`--recursive` option will download submodules (Google Test, Thrust) into the `thirdparty` directory)

## Compilation
In order to compile the library, a C++ compiler must be present. Intel C++ Compiler is advised (versions 14 and 15 were used) to exploit all features of the library. For testing purposes, GNU C++ Compiler (`g++`) may be used as well (at least version 4.6.3).

For compiling code for GPUs, please see paragraph `Running examples on GPU`

**Note: the library is designed to work on Linux. Its behaviour on other systems is undefined. Testing was done on the following distributions: Ubuntu 14.04, Scientific Linux 6.3.**

## Running examples on CPU
1. Enter downloaded directory
2. `make example`
3. `cd examples`
4. Run a selected executable, e.g., `./saxpy`

## Running examples on GPU
**Note that in order to run anything on the GPU, CUDA toolkit must be installed. It can be downloaded from https://developer.nvidia.com/cuda-toolkit**

1. Enter downloaded directory
2. `cd examples`
3. `cd gpu`
4. `make saxpy`
4. If you run the executable: `./saxpy`, it will run on the GPU

## Running tests
1. Enter downloaded directory
2. `make && make tests`

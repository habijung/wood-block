# Untitled

## Build & Run

### Environment

| Name   | Version |
|:-------|:--------|
| OpenGL | 4.1     |
| CMake  | 3.29.2  |
| Ninja  | 1.12.0  |
| GCC    | 13.2.0  |

### Build

**Use shell script**

```shell
sh build.sh
```

**Use command line**

```shell
cmake -S . -B cmake-build -G Ninja -D CMAKE_BUILD_TYPE="Debug"
cmake --build cmake-build -j 10
```

### Run

```shell
./cmake-build/src/untitled.exe
```

---
**Last Updated:** 24.07.16

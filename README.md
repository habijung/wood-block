# Untitled

## Build & Run

### Environment

| Name               | Version |
|:-------------------|:--------|
| OpenGL             | 4.1     |
| CMake              | 3.29.2  |
| Ninja              | 1.12.0  |
| GCC                | 12.2.0  |
| Visual Studio 2022 | 17.8.12 |

### Build

```shell
# Clone repository
git clone https://github.com/habijung/untitled.git

# Update submodule
cd untitled
git submodule update --init --recursive

# CMake generate and build
sh build.sh
```

### Run

```shell
# Windows
./cmake-build/src/untitled.exe
```

---
**Last Updated:** 24.07.22

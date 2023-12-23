# custom-list 
This project is used as a crash test.

## Basic workflow

```bash
cmake -B build -S . -DCMAKE_PREFIX_PATH="/path/to/local_install"
cmake --build build 

# to install
cmake --build build --target install
# to uninstall
cmake --build build --target uninstall
# to clean (assuming you're using Unix MakeFiles, ninja...)
cmake --build build --target clean
```
## Using presets

```bash
cmake --preset default
cmake --build --preset default

# to install
cmake --build --preset install
# to uninstall
cmake --build --preset uninstall
# to clean (assuming you're using Unix MakeFile, ninja...)
cmake --build --preset clean
```

## Using guix

```bash
guix shell --pure gcc-toolchain cmake make coreutils bash -- bash --norc w
```
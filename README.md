# Opengl learning repo

## Compiling instructions:
Compile all executables with `make all`.

To compile a specific exectutables use `make build/<executable_name>` where `<executable_name>` is the name of the source file without the cpp extension. For example, to compile the program `create_triangle2.cpp` executable, use:

```bash
make build/create_triangle2
```

## Known issues
* Code need to be executed from the root of the repo. Otherwise, the shaders won't be found.
* A segmentation fault error is triggered when exiting the program on WSL2. This issue doesn't occur on native linux.
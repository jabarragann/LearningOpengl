# Opengl learning repo

## Dependencies

Install glfw3
```bash
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```
or compiled directly. See [guide to compile and link glfw3](https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project)



Add glad include and src directories.


Copy glm header files into the include folder

## Compiling instructions:
Compile all executables with `make all`.

To compile specific executables, use `make build/<executable_name>` where `<executable_name>` is the name of the source file without the cpp extension. For example, to compile the program `create_triangle2.cpp` executable, use:

```bash
make build/create_triangle2
```

## Opengl learning resources
- [Learnopengl](https://learnopengl.com/)
- [The book of shaders](https://thebookofshaders.com/)
- [glslViewer project](https://github.com/patriciogonzalezvivo/glslViewer/tree/main)
- [Abubujs-Shaders-tutorials](https://www.abubujs.org/learning/tutorials/?help=time-marching-fhn)

## Known issues
* Code needs to be executed from the root of the repo. Otherwise, the shaders won't be found. **Solved:** path to the executable is provided at compilation time with the flag -DBIN_PATH. This flag is used in the code to find the shaders.
* A segmentation fault error is triggered when exiting the program on WSL2. This issue doesn't occur on native Linux.
* GLFW key callbacks is not working well for ubuntu 20.04. Function keys are always returning a value of -1. **Solved:** by compiling GLFW from source.  See [guide to compile and link glfw3](https://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project)

## TODO
* make a folder for executables. Have makefile automatically get all executables from folder.

```bash
js_files  := $(wildcard test/*.js)
all_files := $(shell find images -name "*")
```

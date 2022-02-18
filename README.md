# CG Project - Render 3D Objects from scratch

## Build Instructions
### Clone and initialize repository
```console
$ git clone git@github.com:viniciusrsouza/cg-project.git
$ cd cg-project
$ git submodule update --init --recursive
```

### Build project
```console
$ mkdir build # to avoid poluting the root folder
$ cd build
$ cmake ..
```

The commands above should produce a `cg` executable file inside the build folder.
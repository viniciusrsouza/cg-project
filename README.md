# CG Project - Render 3D Objects from scratch

## Build Instructions
### Clone and initialize repository
```bash
git clone git@github.com:viniciusrsouza/cg-project.git
cd cg-project
git submodule update --init --recursive
```

### Build project
```bash
mkdir build # to avoid poluting the root folder
cd build
cmake ..
make
```

The commands above should produce a `cg` executable file inside the build folder.

### Optional
You can try to increase the amount of jobs (threads) used by make when compiling the source by adding a flag to the command.

```bash
make -j 16 # or the number of jobs you want
```

If building with this flag fails, try building without it. Parallel build might cause issues depending on the order the files are built.
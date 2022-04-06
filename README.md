# CG Project - Render 3D Objects from scratch

## Modules

- `file`: utility functions to handle parsing of byu files.
- `math`: linear algebra library implementing vector and matrix operations.
- `render`: library entrypoint that uses the other modules to implement the scanline conversion algorithm.
- `web`: web application that uses the c++ library to render the objects into a canvas.

## Run Instructions

### Requirements

- node@16.14.0

### Steps

```bash
git clone git@github.com:viniciusrsouza/cg-project.git
cd cg-project/web
npm install
npm start
```

The web server will start listening at `localhost:3000` by default

## Build project

The rendering algorithm is made in C++ and compiled to WebAssembly to run in the browser. Inside the web folder there is already a pre-compiled version of the code, but if you want to try and compile it yourself, follow the next steps.

### Requirementes

The project might build with versions older than the specified, but those were the versions used during development

- [Emscripten@3.1.6](https://emscripten.org)
- [CMake@3.22.0](https://cmake.org)

### Steps

```bash
mkdir em-build
cd em-build
emcmake cmake ..
emmake make
```

The commands above will build and copy the `wasm` file and the javascript wrappers into the `/web/public/dist/` folder, after that you can follow the steps to run the project.

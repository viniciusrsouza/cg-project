/* global Module FS */

const files = [
  "calice2.byu",
  "maca.byu",
  "maca2.byu",
  "piramide.byu",
  "triangulo.byu",
  "vaso.byu",
];

Module.onRuntimeInitialized = () => {
  const asset = files[5];
  load_assets().then(() => run_c_render(asset));
};

async function load_assets() {
  for (const file of files) {
    const res = await fetch(`/assets/${file}`);
    const data = await res.text();
    Module["FS_createDataFile"]("/tmp", file, data, true, true);
  }
}

async function run_c_render(asset) {
  function farrayToPtr(arr) {
    const ptr = Module._malloc(arr.length * 4);
    Module.HEAPF32.set(arr, ptr / 4);
    return ptr;
  }

  function arrayToPtr(array) {
    const ptr = Module._malloc(array.length);
    Module.HEAPU8.set(array, ptr);
    return ptr;
  }

  function ptrToArray(ptr, length) {
    const array = new Uint8ClampedArray(length);
    const pos = ptr;
    array.set(Module.HEAPU8.subarray(pos, pos + length));
    return array;
  }

  const c_render = Module.cwrap("c_render", null, [
    "number",
    "number",
    "number",
    "number",
  ]);

  const asset_ptr = Module.allocateUTF8(`/tmp/${asset}`);
  const camera = new Float32Array([0, 1, -1, 0, -1, -1, 5, 2, 2, 0, -500, 500]);
  const camera_ptr = farrayToPtr(camera);
  const w = 400;
  const h = 400;
  const ptr = c_render(asset_ptr, camera_ptr, w, h);
  const array = ptrToArray(ptr, w * h * 4);

  const canvas = document.getElementById("canvas");
  const ctx = canvas.getContext("2d");
  const imageData = ctx.createImageData(w, h);
  imageData.data.set(array);
  ctx.putImageData(imageData, 0, 0);
}

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
  const asset = files[0];
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
  const camera = get_camera_values();
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

function get_vector_inputs(vector) {
  const vec_x = document.getElementById(`${vector}_x`).value;
  const vec_y = document.getElementById(`${vector}_y`).value;
  const vec_z = document.getElementById(`${vector}_z`).value;
  return [parseFloat(vec_x), parseFloat(vec_y), parseFloat(vec_z)];
}

function get_camera_values() {
  const [nx, ny, nz] = get_vector_inputs("n");
  const [vx, vy, vz] = get_vector_inputs("v");
  const [cx, cy, cz] = get_vector_inputs("c");
  const d = parseFloat(document.getElementById("d").value);
  const hx = parseFloat(document.getElementById("hx").value);
  const hy = parseFloat(document.getElementById("hy").value);
  const camera_array = [nx, ny, nz, vx, vy, vz, d, hx, hy, cx, cy, cz];
  return new Float32Array(camera_array);
}

window.onload = () => {
  const selection = document.getElementById("file-select");
  const fileOptions = files.map((file) => {
    const option = document.createElement("option");
    option.text = file;
    option.value = file;
    return option;
  });
  fileOptions.forEach((option) => selection.add(option));
  selection.onchange = () => {
    const asset = selection.value;
    run_c_render(asset);
  };

  const apply_btn = document.getElementById("cam-btn");
  apply_btn.onclick = () => {
    const asset = selection.value;
    run_c_render(asset);
  };
};

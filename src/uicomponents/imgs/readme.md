# Notes on images

The table below lists all the original images:

| image            | Source                           | url                                                                                                                                             |
| ---------------- | -------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| brightness.svg   | Material Design Icons            | https://pictogrammers.com/library/mdi/icon/brightness-6/                                                                                        |
| colortemp24.png  | Ruben created it in gimp         | N/A                                                                                                                                             |
| colorwheel96.png | Copy from HA's CSS Implmentation | https://github.com/home-assistant/frontend/blob/4f01348ffb5760f9bcf5abec5be19b194a56c9c1/src/dialogs/more-info/controls/more-info-light.ts#L207 |
| white.svg        | Material Design Icons            | https://pictogrammers.com/library/mdi/icon/file-word-box/                                                                                       |

These images are then resized to the size that we need and converted (if it's a svg) to a png.
Once we have the size that we need, we've taken through the [online image conversion tool](https://lvgl.io/tools/imageconverter) with the following settings:
- color format = CF_TRUE_COLOR_ALPHA
- output = C array
- Dither images = unchecked
- output in big-endian format = unchecked

This produces a .cpp file which is also in this directory.
We keep all files:
- original file
- If it was a svg that the online image converter didn't like, we store the png in original size
- resized png file
- outputted cpp file

The CPP file has some small modifications. At the end of the file, there's a section for the headers:

```cpp
const lv_img_dsc_t colorwheel24 = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 24,
  .header.h = 24,
  .data_size = 576 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = colorwheel24_map,
};
```

This does not work for our clang-tidy and thus, we convert it to:

```cpp
const lv_img_header_t colorwheel24header = {
  .cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .always_zero = 0,
  .reserved = 0,
  .w = 24,
  .h = 24,
};

const lv_img_dsc_t colorwheel24 = {
  .header = colorwheel24header,
  .data_size = 576 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = colorwheel24_map,
};

```


We also store the original pictures in this folder, so that we can always go back to them. In some cases the orginal is a SVG, that we then first save as a PNG.



The .cpp files here are generated, but they have to be modified to work. The `lv_img_header_t` in the generated code is not accepted by our CPP, so we modify that manually.


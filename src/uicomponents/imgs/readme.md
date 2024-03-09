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

This produces a .c file which is also in this directory.
We keep all files:
- original file
- If it was a svg that the online image converter didn't like, we store the png in original size
- resized png file
- outputted cpp file

The .c file has some small modifications, because of clang-format, and in the includes.

We also store the original pictures in this folder, so that we can always go back to them. In some cases the orginal is a SVG, that we then first save as a PNG.

The .cpp files here are generated, but they have to be modified to work. The `lv_img_header_t` in the generated code is not accepted by our CPP, so we modify that manually.

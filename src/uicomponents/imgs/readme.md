# Notes on images

There's a few images in this directory. We converted them using the [online image conversion tool](https://lvgl.io/tools/imageconverter) to an array. Settings in the online conversion tool:
- color format = CF_TRUE_COLOR_ALPHA
- output = C array
- Dither images = unchecked
- output in big-endian format = unchecked

We use the amount of pixels at the end of the filename. So brightness24.cpp has height and width of 24 pixels.
We also store the original pictures in this folder, so that we can always go back to them. In some cases the orginal is a SVG, that we then first save as a PNG.


## Generated code
So, the .cpp files here are generated, but they have to be modified to work. The `lv_img_header_t` in the generated code is not accepted by our CPP, so we modify that manually.

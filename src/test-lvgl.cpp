#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "main.hpp"
#include "WSConn.hpp"
#include "Backend.hpp"
#include "HAEntity.hpp"

#include "logger.hpp"

using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::flush;

#include <memory>
#include <lvgl.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style.h>
#include <src/font/lv_font.h>
#include <src/font/lv_symbol_def.h>
#include <src/indev/lv_indev.h>
#include <src/libs/tiny_ttf/lv_tiny_ttf.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_style.h>

// make sure these numbers align with SDL_HOR_RES/SDL_VER_RES
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480
#define DISP_BUF_SIZE 16384

extern unsigned char B612_Regular_ttf[];
extern unsigned int B612_Regular_ttf_len;

int main(int _argc, char* _argv[])
{
  g_log << Logger::Debug << "calling lv_init()" << std::endl;
  lv_init();
#if defined(VOORKANT_LVGL_SDL)
  g_log << Logger::Debug << "calling sdl_init()" << std::endl;
  // sdl_init();
#elif defined(VOORKANT_LVGL_FBDEV)
  g_log << Logger::Debug << "calling fbdev_init()" << std::endl;
  // fbdev_init();
#else
#error "no useful VOORKANT_LVGL_* found"
#endif

  /*Create a display buffer*/
#if defined(VOORKANT_LVGL_SDL)
  static lv_display_t* disp = lv_sdl_window_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
#elif defined(VOORKANT_LVGL_FBDEV)
  static lv_display_t* disp = lv_linux_fbdev_create();
  lv_linux_fbdev_set_file(disp, "/dev/fb0");
#endif
  // static lv_color_t buf_1[DISP_BUF_SIZE];
  // static lv_color_t buf_2[DISP_BUF_SIZE];
  // lv_display_set_buffers(disp, buf_1, buf_2, DISP_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL); // FIXME ponder what mode we want

  // lv_display_drv_t disp_drv; /*A variable to hold the drivers. Can be local variable*/
  // lv_display_drv_init(&disp_drv); /*Basic initialization*/
  // disp_drv.hor_res = MY_DISP_HOR_RES;
  // disp_drv.ver_res = MY_DISP_VER_RES;
  // disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
#if defined(VOORKANT_LVGL_SDL)
  // lv_display_set_flush_cb(disp, sdl_display_flush);
#elif defined(VOORKANT_LVGL_FBDEV)
  // lv_display_set_flush_cb(disp, fbdev_flush);
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  /*lv_display_t* disp;*/
  // /*disp = */ lv_display_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

// #if 0
#if defined(VOORKANT_LVGL_FBDEV)
  // evdev_init();
#endif
  // lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
#if defined(VOORKANT_LVGL_SDL)
  static lv_indev_t* indev = lv_sdl_mouse_create();
  // lv_indev_set_read_cb(indev, sdl_mouse_read);
#elif defined(VOORKANT_LVGL_FBDEV)
  static lv_indev_t* indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event0");
  lv_evdev_set_calibration(indev, 200, 3850, 3600, 320);
  lv_indev_set_display(indev, disp);
  // enc_drv.read_cb = evdev_read;
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  // /*lv_indev_t* enc_indev = */ lv_indev_drv_register(&enc_drv);
  // #endif
  // lv_indev_set_group(enc_indev, g);
  // lv_group_t* g = lv_group_create();
  // lv_group_set_default(g);

  static lv_font_t* B612font = lv_tiny_ttf_create_data_ex(B612_Regular_ttf, B612_Regular_ttf_len, 16, LV_FONT_KERNING_NORMAL, 1024);
  static lv_style_t B612style;
  lv_style_init(&B612style);
  lv_style_set_text_font(&B612style, B612font);

  lv_layer_t layer;
  lv_obj_t * canvas;
  lv_draw_buf_t * canvas_buf;
  
  canvas = lv_canvas_create(lv_scr_act());
  canvas_buf = lv_draw_buf_create(480, 480, LV_COLOR_FORMAT_ARGB8888, 0);
  lv_canvas_set_draw_buf(canvas, canvas_buf);
  lv_canvas_fill_bg(canvas, lv_color_make(0xff, 0xff, 0xff), 255);
  lv_canvas_init_layer(canvas, &layer);

  const char * svg_group_1 = \
                             "<svg><g fill=\"#FF0000\">"
                             "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\"/>"
                             "<circle cx=\"100\" cy=\"100\" r=\"50\"/>"
                             "<ellipse fill=\"#00F\" cx=\"200\" cy=\"200\" rx=\"100\" ry=50/>"
                             "</g></svg>";

  lv_svg_node_t * svg = lv_svg_load_data(svg_group_1, lv_strlen(svg_group_1));
  lv_image_cache_drop(canvas_buf);
  lv_canvas_set_draw_buf(canvas, canvas_buf);
  lv_canvas_fill_bg(canvas, lv_color_make(0xff, 0xff, 0xff), 255);
  lv_draw_svg(&layer, svg);
  lv_canvas_finish_layer(canvas, &layer);  lv_svg_node_delete(svg);

  int i = 0;
  LV_LOG_ERROR("testing log");

  while (true) {
    // FIXME: fixed sleeps + non-fixed actions between the sleeps means we don't run the ticks as often as we say we do
    // possibly helpful (thanks dwfreed): https://en.cppreference.com/w/cpp/thread/sleep_until

    usleep(5 * 1000); // 5000 usec = 5 ms
    {
      lv_tick_inc(5); // 5 ms
      lv_task_handler();
    }
    if (i++ == (1000 / 5)) {
      cerr << "." << flush;
      i = 0;
    }
  }
}

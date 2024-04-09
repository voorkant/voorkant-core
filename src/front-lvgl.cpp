#include "front-lvgl.hpp"
#include "HAEntity.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/UILogBox.hpp"
#include <src/core/lv_event.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style.h>
#include <src/extra/layouts/flex/lv_flex.h>
#include <src/font/lv_symbol_def.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_style.h>
#include <src/widgets/lv_btn.h>
#include <src/widgets/lv_label.h>
#include <src/widgets/lv_textarea.h>

// make sure these numbers align with SDL_HOR_RES/SDL_VER_RES
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480
#define DISP_BUF_SIZE 16384

std::mutex g_lvgl_updatelock;
lv_obj_t* cont_row;
namespace
{
template <typename UIType>
std::unique_ptr<UIEntity> makeUIElement(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent)
{
  return std::make_unique<UIType>(_entity, _parent);
}
}

void btnLeftPress(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);
  if (code == LV_EVENT_CLICKED) {
    lv_coord_t x = lv_obj_get_scroll_x(cont_row);
    cerr << "Left press: " << x << endl;

    // this is 807 because for whatever reason the snapping requires it to be 807....
    lv_obj_scroll_to_x(cont_row, x - 807, LV_ANIM_OFF);
  }
};

void btnRightPress(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);
  if (code == LV_EVENT_CLICKED) {
    lv_coord_t x = lv_obj_get_scroll_x(cont_row);
    cerr << "Right press: " << x << endl;
    lv_obj_scroll_to_x(cont_row, x + 807, LV_ANIM_OFF);
  }
};

void uithread(HABackend& _backend, int _argc, char* _argv[])
{
  argparse::ArgumentParser program("client-lvgl");

  argparse::ArgumentParser entity_command("entity");
  entity_command.add_argument("pattern")
    .help("what entity to render, in a c++ regex");

  program.add_subparser(entity_command);

  try {
    program.parse_args(_argc, _argv);
  }
  catch (const std::runtime_error& err) {
    cerr << err.what() << endl;
    cerr << program;
    return;
  }

  if (program.is_subcommand_used(entity_command)) {
    // FIXME: now actually use the argument
    //    current_light = entity_command.get<string>("name");
    //  cerr << "should render " << current_light << endl;
  }
  else {
    cerr << "no command given" << endl;
    return;
  }

  _backend.start();

  cerr << "calling lv_init" << endl;
  lv_init();
#if defined(VOORKANT_LVGL_SDL)
  sdl_init();
#elif defined(VOORKANT_LVGL_FBDEV)
  fbdev_init();
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  cerr << "called fbdev_init" << endl;

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf;
  static lv_color_t buf_1[DISP_BUF_SIZE];
  static lv_color_t buf_2[DISP_BUF_SIZE];
  lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);

  lv_disp_drv_t disp_drv; /*A variable to hold the drivers. Can be local variable*/
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.hor_res = MY_DISP_HOR_RES;
  disp_drv.ver_res = MY_DISP_VER_RES;
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
#if defined(VOORKANT_LVGL_SDL)
  disp_drv.flush_cb = sdl_display_flush;
#elif defined(VOORKANT_LVGL_FBDEV)
  disp_drv.flush_cb = fbdev_flush; /*Set a flush callback to draw to the display*/
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  /*lv_disp_t* disp;*/
  /*disp = */ lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

// #if 0
#if defined(VOORKANT_LVGL_FBDEV)
  evdev_init();
#endif
  lv_indev_drv_t enc_drv;
  lv_indev_drv_init(&enc_drv);
  enc_drv.type = LV_INDEV_TYPE_POINTER;
#if defined(VOORKANT_LVGL_SDL)
  enc_drv.read_cb = sdl_mouse_read;
#elif defined(VOORKANT_LVGL_FBDEV)
  enc_drv.read_cb = evdev_read;
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  /*lv_indev_t* enc_indev = */ lv_indev_drv_register(&enc_drv);
  // #endif
  // lv_indev_set_group(enc_indev, g);
  // lv_group_t* g = lv_group_create();
  // lv_group_set_default(g);

  /* container for object row (top 80% of screen) and logs (bottom 20%) */
  lv_obj_t* row_and_logs = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(row_and_logs);
  lv_obj_clear_flag(row_and_logs, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(row_and_logs, MY_DISP_HOR_RES, MY_DISP_VER_RES);
  lv_obj_set_flex_flow(row_and_logs, LV_FLEX_FLOW_ROW_WRAP);

  /*Create a container with ROW flex direction that wraps.
  This is our MAIN box that we put everything in except logs. We have this here because we want some spacing around it.
  */
  cont_row = lv_obj_create(row_and_logs);
  lv_obj_remove_style_all(cont_row);
  lv_obj_set_size(cont_row, MY_DISP_HOR_RES, MY_DISP_VER_RES * 0.8);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_COLUMN_WRAP);
  lv_obj_set_style_pad_row(cont_row, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(cont_row, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_scroll_snap_x(cont_row, LV_SCROLL_SNAP_START);

  /* Bottom row */
  lv_obj_t* bottom_row = lv_obj_create(row_and_logs);
  lv_obj_remove_style_all(bottom_row);
  lv_obj_set_size(bottom_row, MY_DISP_HOR_RES, MY_DISP_VER_RES * 0.2);
  lv_obj_set_align(bottom_row, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(bottom_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(bottom_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END);

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_bg_color(&style, lv_color_hex(0xc0c0c0));
  lv_style_set_radius(&style, lv_coord_t(0));
  lv_obj_add_style(bottom_row, &style, 0);

  lv_obj_t* left_btn = lv_btn_create(bottom_row);
  lv_obj_t* left_btn_txt = lv_label_create(left_btn);
  lv_label_set_text(left_btn_txt, LV_SYMBOL_LEFT);
  lv_obj_add_event_cb(left_btn, btnLeftPress, LV_EVENT_CLICKED, NULL);

  UILogBox logbox(bottom_row);

  lv_obj_t* right_btn = lv_btn_create(bottom_row);
  lv_obj_t* right_btn_txt = lv_label_create(right_btn);
  lv_label_set_text(right_btn_txt, LV_SYMBOL_RIGHT);
  lv_obj_add_event_cb(right_btn, btnRightPress, LV_EVENT_CLICKED, NULL);

  // FIXME: does this actually need unique_ptr? I guess it might save some copying
  std::vector<std::unique_ptr<UIEntity>> uielements;

  using MakeUIElementType = std::unique_ptr<UIEntity> (*)(std::shared_ptr<HAEntity>, lv_obj_t*);

  std::map<EntityType, MakeUIElementType> make_element_map{
    {EntityType::Light, makeUIElement<UIRGBLight>},
    {EntityType::Switch, makeUIElement<UISwitch>},
    {EntityType::Fan, makeUIElement<UIButton>},
    {EntityType::Camera, makeUIElement<UICamera>},
    {EntityType::OTHER, makeUIElement<UIDummy>}};

  auto entities = _backend.getEntitiesByPattern(entity_command.get<string>("pattern"));
  std::cerr << "Entities are: " << entities.size() << std::endl;
  for (const auto& entity : entities) {
    // FIXME: this is very simple and should move to something with panels in HA.
    uielements.push_back(make_element_map[entity->getEntityType()](entity, cont_row));
  }
  int i = 0;
  while (true) {
    usleep(5 * 1000); // 5000 usec = 5 ms
    {
      std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
      lv_tick_inc(5); // 5 ms
      lv_task_handler();
    }
    if (i++ == (1000 / 5)) {
      cerr << "." << flush;
      i = 0;
    }
  }
}
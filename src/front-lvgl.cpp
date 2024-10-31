#include "front-lvgl.hpp"
#include "Backend.hpp"
#include "HAEntity.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/UILogBox.hpp"
#include "uicomponents/uirgblight.hpp"
#include <memory>
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
extern unsigned char mdi_ttf[];
extern unsigned int mdi_ttf_len;

namespace voorkant
{
namespace lvgl
{
  lv_font_t* b612font;
  lv_style_t b612style;
  lv_font_t* mdifont;
  lv_style_t mdistyle;
}
}

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
    // this is 807 because for whatever reason the snapping requires it to be 807....
    lv_obj_scroll_to_x(cont_row, x - 807, LV_ANIM_OFF);
  }
};

void btnRightPress(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);
  if (code == LV_EVENT_CLICKED) {
    lv_coord_t x = lv_obj_get_scroll_x(cont_row);
    lv_obj_scroll_to_x(cont_row, x + 807, LV_ANIM_OFF);
  }
};

void lvLogCallback(lv_log_level_t _level, const char* _buf) // FIXME use level
{
  g_log << Logger::Error << _buf << endl;
}

void uithread(int _argc, char* _argv[])
{
  argparse::ArgumentParser program("voorkant-lvgl", getVersion());

  argparse::ArgumentParser entity_command("entity");
  entity_command.add_argument("pattern").help("what entity to render, in a c++ regex");
  program.add_subparser(entity_command);

  argparse::ArgumentParser dashboard_command("dashboard");
  dashboard_command.add_argument("dashboard-name").help("provide a Home Assistant panel name");
  program.add_subparser(dashboard_command);

  try {
    program.parse_args(_argc, _argv);
  }
  catch (const std::runtime_error& err) {
    cerr << err.what() << endl;
    cerr << program;
    return;
  }

  if (!program.is_subcommand_used(entity_command) && !program.is_subcommand_used(dashboard_command)) {
    cerr << "no command given" << endl;
    return;
  }

  HABackend::getInstance().start();

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

  voorkant::lvgl::b612font = lv_tiny_ttf_create_data_ex(B612_Regular_ttf, B612_Regular_ttf_len, 16, LV_FONT_KERNING_NORMAL, 1024);
  lv_style_init(&voorkant::lvgl::b612style);
  lv_style_set_text_font(&voorkant::lvgl::b612style, voorkant::lvgl::b612font);

  voorkant::lvgl::mdifont = lv_tiny_ttf_create_data_ex(mdi_ttf, mdi_ttf_len, 16, LV_FONT_KERNING_NORMAL, 1024);
  lv_style_init(&voorkant::lvgl::mdistyle);
  lv_style_set_text_font(&voorkant::lvgl::mdistyle, voorkant::lvgl::mdifont);

  lv_obj_add_style(lv_scr_act(), &voorkant::lvgl::b612style, 0);

  /* container for object row (top 80% of screen) and logs (bottom 20%) */
  lv_obj_t* row_and_logs = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(row_and_logs);
  lv_obj_remove_flag(row_and_logs, LV_OBJ_FLAG_SCROLLABLE);
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

  lv_obj_t* left_btn = lv_button_create(bottom_row);
  lv_obj_t* left_btn_txt = lv_label_create(left_btn);
  lv_label_set_text(left_btn_txt, MDI_ARROW_LEFT);
  lv_obj_add_event_cb(left_btn, btnLeftPress, LV_EVENT_CLICKED, NULL);
  lv_obj_add_style(left_btn, &voorkant::lvgl::mdistyle, 0);

  UILogBox logbox(bottom_row, &voorkant::lvgl::b612style);

  lv_obj_t* right_btn = lv_button_create(bottom_row);
  lv_obj_t* right_btn_txt = lv_label_create(right_btn);
  lv_label_set_text(right_btn_txt, MDI_ARROW_RIGHT);
  lv_obj_add_style(right_btn_txt, &voorkant::lvgl::mdistyle, 0);

  lv_obj_add_event_cb(right_btn, btnRightPress, LV_EVENT_CLICKED, NULL);

  lv_log_register_print_cb(lvLogCallback);

  std::vector<std::unique_ptr<UIEntity>> uielements;
  if (program.is_subcommand_used(entity_command)) {
    // FIXME: does this actually need unique_ptr? I guess it might save some copying

    using MakeUIElementType = std::unique_ptr<UIEntity> (*)(std::shared_ptr<HAEntity>, lv_obj_t*);

    std::map<EntityType, MakeUIElementType> make_element_map{
      {EntityType::Light, makeUIElement<UIRGBLight>},
      {EntityType::Switch, makeUIElement<UISwitch>},
      {EntityType::Fan, makeUIElement<UIButton>},
      {EntityType::Sensor, makeUIElement<UISensor>},
      {EntityType::OTHER, makeUIElement<UIDummy>}};

    auto entities = HABackend::getInstance().getEntitiesByPattern(entity_command.get<string>("pattern"));
    g_log << Logger::Debug << "Entities are: " << entities.size() << std::endl;
    for (const auto& entity : entities) {
      // FIXME: this is very simple and should move to something with panels in HA.
      uielements.push_back(make_element_map[entity->getEntityType()](entity, cont_row));
    }
  }
  else if (program.is_subcommand_used(dashboard_command)) {
    json doc = HABackend::getInstance().getDashboardConfig(dashboard_command.get<string>("dashboard-name"));

    if (doc.contains("error")) {
      g_log << Logger::Error << "Failed to get dashboard configuration:" << std::endl;
      g_log << Logger::Error << doc << std::endl;
      exit(-1);
    }

    // FIXME: lots of repeat code here, should do a <template> thing
    json result = doc["result"];
    for (auto view : result["views"]) {
      for (auto card : view["cards"]) {
        if (card["type"] == "entities") {
          if (card.contains("entities")) { // array of objects with the entity name in it.
            auto objs = card["entities"];
            for (auto ent : objs) {
              string entityname;
              if (ent.type() == json::value_t::string) {
                entityname = ent;
              }
              else {
                entityname = ent["entity"];
              }
              std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
              if (entity->getEntityType() == EntityType::Light) {
                std::unique_ptr<UIEntity> btn = std::make_unique<UISwitch>(entity, cont_row);
                uielements.push_back(std::move(btn));
              }
              else if (entity->getEntityType() == EntityType::Switch) {
                std::unique_ptr<UIEntity> btn = std::make_unique<UISwitch>(entity, cont_row);
                uielements.push_back(std::move(btn));
              }
              else if (entity->getEntityType() == EntityType::Sensor) {
                std::unique_ptr<UIEntity> sensor = std::make_unique<UISensor>(entity, cont_row);
                uielements.push_back(std::move(sensor));
              }
              else {
                std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
                std::unique_ptr<UIEntity> dummy = std::make_unique<UIDummy>(entity, cont_row);
                uielements.push_back(std::move(dummy));
              }
            }
          }
        }
        else if (card["type"] == "button") {
          if (card.contains("entity")) {
            string entityname = card["entity"];
            std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
            std::unique_ptr<UIEntity> btn = std::make_unique<UIButton>(entity, cont_row);
            uielements.push_back(std::move(btn));
          }
          else {
            g_log << Logger::Warning << "Card is of type button, but no entity found: " << card << std::endl;
          }
        }
        else if (card["type"] == "light") {
          if (card.contains("entity")) {
            string entityname = card["entity"];
            std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
            std::unique_ptr<UIEntity> btn = std::make_unique<UIRGBLight>(entity, cont_row);
            uielements.push_back(std::move(btn));
          }
          else {
            g_log << Logger::Warning << "Card is of type button, but no entity found: " << card << std::endl;
          }
        }
        // else if (card["type"] == "custom:apexcharts-card") {

        //   std::unique_ptr<UIEntity> apex = std::make_unique<UIApexCard>(card, cont_row);
        //   uielements.push_back(std::move(apex));
        //   g_log << Logger::Warning << "got apex card" << std::endl;
        // }
        else {
          if (card.contains(("entity"))) {
            g_log << Logger::Warning << "Card of type " << card["type"] << " found, but we have no matching UIEntity. Creating dummy for entity." << card["entity"] << std::endl;
            string entityname = card["entity"];
            std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
            std::unique_ptr<UIEntity> dummy = std::make_unique<UIDummy>(entity, cont_row);
            uielements.push_back(std::move(dummy));
          }
          else {
            g_log << Logger::Warning << "Card of type " << card["type"] << " found, couldn't find entity." << std::endl;
          }
        }
      } // for card
    } // for views
  }
  else {
    g_log << Logger::Info << "We expected a command" << std::endl;
    exit(1);
  }

  int i = 0;
  LV_LOG_ERROR("testing logbox");

  while (true) {
    // FIXME: fixed sleeps + non-fixed actions between the sleeps means we don't run the ticks as often as we say we do
    // possibly helpful (thanks dwfreed): https://en.cppreference.com/w/cpp/thread/sleep_until

    usleep(5 * 1000); // 5000 usec = 5 ms
    {
      std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
      lv_tick_inc(5); // 5 ms
      lv_task_handler();
    }
    logbox.updateIfNeeded();
    if (i++ == (1000 / 5)) {
      cerr << "." << flush;
      i = 0;
    }
  }
}

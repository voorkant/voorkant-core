#include "front-lvgl.hpp"
#include "Backend.hpp"
#include "HAEntity.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/UILogBox.hpp"
#include "uicomponents/uirgblight.hpp"
#include "uicomponents/mdimap.hpp"
#include <memory>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/font/lv_font.h>
#include <src/font/lv_symbol_def.h>
#include <src/indev/lv_indev.h>
#include <src/layouts/grid/lv_grid.h>
#include <src/libs/tiny_ttf/lv_tiny_ttf.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
#include <src/misc/lv_style.h>
#include <src/widgets/tabview/lv_tabview.h>
#include <stdexcept>
#include <string>

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
  lv_font_t* b612fontbig;
  lv_style_t b612stylebig;
  lv_font_t* mdifont;
  lv_style_t mdistyle;
  map<iconkey, string> iconmap; // will need a lock eventually
  json iconcomponentmap; // lock?
}
}

std::mutex g_lvgl_updatelock;
namespace
{
template <typename UIType>
std::unique_ptr<UIEntity> makeUIElement(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent)
{
  return std::make_unique<UIType>(_entity, _parent);
}
}

void lvLogCallback(lv_log_level_t _level, const char* _buf) // FIXME use level
{
  g_log << Logger::Error << _buf << endl;
}

static lv_obj_t* clocklabel{nullptr};

void renderCard(std::vector<std::unique_ptr<UIEntity>>& _uielements, nlohmann::basic_json<>& _card, lv_obj_t* _parent)
{
  if (_card["type"] == "entities") {
    if (_card.contains("entities")) { // array of objects with the entity name in it.
      auto objs = _card["entities"];
      for (auto ent : objs) {
        string entityname;
        string icon;
        if (ent.type() == json::value_t::string) {
          entityname = ent;
        }
        else {
          entityname = ent["entity"];
          icon = ent.value("icon", "");
        }
        std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
        if (entity->getEntityType() == EntityType::Light) {
          std::unique_ptr<UIEntity> btn = std::make_unique<UISwitch>(entity, _parent);
          _uielements.push_back(std::move(btn));
        }
        else if (entity->getEntityType() == EntityType::Switch) {
          std::unique_ptr<UIEntity> btn = std::make_unique<UISwitch>(entity, _parent);
          _uielements.push_back(std::move(btn));
        }
        else if (entity->getEntityType() == EntityType::Sensor || true) {
          // we used to fall back to UIDummy, but UISensor actually shows things better than that,
          // hence the || true. If you add a type, put it above.
          std::unique_ptr<UIEntity> sensor = std::make_unique<UISensor>(entity, _parent, icon);
          _uielements.push_back(std::move(sensor));
        }
      }
    }
  }
  else if (_card["type"] == "button") {
    if (_card.contains("entity")) {
      string entityname = _card["entity"];
      std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
      std::unique_ptr<UIEntity> btn = std::make_unique<UIButton>(entity, _parent);
      _uielements.push_back(std::move(btn));
    }
    else {
      g_log << Logger::Warning << "Card is of type button, but no entity found: " << _card << std::endl;
    }
  }
  else if (_card["type"] == "light") {
    if (_card.contains("entity")) {
      string entityname = _card["entity"];
      std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
      std::unique_ptr<UIEntity> btn = std::make_unique<UIRGBLight>(entity, _parent);
      _uielements.push_back(std::move(btn));
    }
    else {
      g_log << Logger::Warning << "Card is of type light, but no entity found: " << _card << std::endl;
    }
  }
  else if (_card["type"] == "custom:apexcharts-card") {

    std::unique_ptr<UIEntity> apex = std::make_unique<UIApexCard>(_card, _parent);
    _uielements.push_back(std::move(apex));
    g_log << Logger::Warning << "got apex card" << std::endl;
  }
  else {
    if (_card.contains(("entity"))) {
      g_log << Logger::Warning << "Card of type " << _card["type"] << " found, but we have no matching UIEntity. Falling back to 'sensor' for entity." << _card["entity"] << std::endl;
      string entityname = _card["entity"];
      std::shared_ptr<HAEntity> entity = HABackend::getInstance().getEntityByName(entityname);
      std::unique_ptr<UIEntity> sensor = std::make_unique<UISensor>(entity, _parent);
      _uielements.push_back(std::move(sensor));
    }
    else {
      g_log << Logger::Warning << "Card of type " << _card["type"] << " found, couldn't find entity." << std::endl;
    }
  }
}

void renderSection(std::vector<std::unique_ptr<UIEntity>>& _uielements, nlohmann::basic_json<>& _section, lv_obj_t* _parent)
{
  auto section = lv_obj_create(_parent);
  lv_obj_remove_style_all(section);
  lv_obj_set_height(section, lv_pct(100));
  lv_obj_set_flex_flow(section, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_grow(section, 1);
  lv_obj_set_style_pad_row(section, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(section, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_scroll_snap_x(section, LV_SCROLL_SNAP_START);
  lv_obj_remove_flag(section, LV_OBJ_FLAG_SCROLLABLE);

  for (auto card : _section["cards"]) {
    renderCard(_uielements, card, section);
  }
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

  voorkant::lvgl::mdifont = lv_tiny_ttf_create_data_ex(mdi_ttf, mdi_ttf_len, 30, LV_FONT_KERNING_NORMAL, 1024);
  lv_style_init(&voorkant::lvgl::mdistyle);
  lv_style_set_text_font(&voorkant::lvgl::mdistyle, voorkant::lvgl::mdifont);

  lv_obj_add_style(lv_scr_act(), &voorkant::lvgl::b612style, 0);

  int32_t reserved_at_top = 0;
  auto resvar = getenv("VOORKANT_LVGL_LINES_RESERVED_AT_TOP");

  if (resvar != nullptr) {
    reserved_at_top = std::stoi(resvar);
    if (reserved_at_top < 0) {
      throw std::runtime_error("can't reserve a negative amount of lines");
    }
  }

  static lv_obj_t* splitparent = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(splitparent);
  lv_obj_remove_flag(splitparent, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(splitparent, lv_pct(100), lv_pct(100));

  lv_obj_set_layout(splitparent, LV_LAYOUT_GRID);
  static lv_coord_t splitparent_col_dsc[] = {LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static lv_coord_t splitparent_row_dsc[] = {reserved_at_top, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(splitparent, splitparent_col_dsc, splitparent_row_dsc);

  static lv_obj_t* reserved = lv_obj_create(splitparent);
  lv_obj_remove_style_all(reserved);
  lv_obj_remove_flag(reserved, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_grid_cell(reserved, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_obj_set_style_bg_opa(reserved, LV_OPA_TRANSP, 0);

  static lv_obj_t* content = lv_obj_create(splitparent);
  lv_obj_remove_style_all(content);
  lv_obj_remove_flag(content, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_grid_cell(content, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);

  /* container for object row (top 80% of screen) and logs (bottom 20%) */
  lv_obj_t* row_and_logs = lv_obj_create(content);
  lv_obj_remove_style_all(row_and_logs);
  lv_obj_remove_flag(row_and_logs, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_size(row_and_logs, lv_pct(100), lv_pct(100));
  // lv_obj_set_y(row_and_logs, reserved_at_top);
  lv_obj_set_flex_flow(row_and_logs, LV_FLEX_FLOW_ROW_WRAP);

  /*Create a container with ROW flex direction that wraps.
  This is our MAIN box that we put everything in except logs. We have this here because we want some spacing around it.
  */
  static auto cont_row = lv_obj_create(row_and_logs);
  lv_obj_remove_style_all(cont_row);
  lv_obj_set_size(cont_row, lv_pct(100), lv_pct(80));

  /* Bottom row */
  lv_obj_t* bottom_row = lv_obj_create(row_and_logs);
  lv_obj_remove_style_all(bottom_row);
  lv_obj_set_size(bottom_row, lv_pct(100), lv_pct(20));
  lv_obj_set_align(bottom_row, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(bottom_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(bottom_row, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END);

  static lv_style_t style;
  lv_style_init(&style);
  lv_style_set_bg_color(&style, lv_color_hex(0xc0c0c0));
  lv_style_set_radius(&style, lv_coord_t(0));
  lv_obj_add_style(bottom_row, &style, 0);

  UILogBox logbox(bottom_row, &voorkant::lvgl::b612style);

  lv_log_register_print_cb(lvLogCallback);

  std::vector<std::unique_ptr<UIEntity>> uielements;
  std::vector<lv_obj_t*> viewtabs;
  if (program.is_subcommand_used(entity_command) || program.is_subcommand_used(dashboard_command)) {
    // need to collect some data used in both cases

    auto& ha = HABackend::getInstance();

    // FIXME: -cli, -ftxui don't need list_for_display or get_icons
    json list_for_display = ha.doCommand("config/entity_registry/list_for_display", {});

    cerr << list_for_display.dump(2) << endl;
    std::set<string> integrations;
    for (auto ent : list_for_display["result"]["entities"]) {
      auto entity_id = ent["ei"].get<std::string>();
      auto platform = ent.value("pl", "");
      auto translation_key = ent.value("tk", "");
      integrations.insert(platform);

      auto entity = ha.getEntityByName(entity_id);
      entity->platform = platform;
      entity->translation_key = translation_key;
    }
    json get_icons_req;
    get_icons_req["category"] = "entity"; // wonder what other categories there are. platform? integration? need to find frank somewhere

    json get_icons = ha.doCommand("frontend/get_icons", get_icons_req);
    // inside "resources":
    //      "sun": {
    //        "sensor": {
    //          "next_dawn": {
    //            "default": "mdi:sun-clock"
    //          },
    //          "next_dusk": {
    //            "default": "mdi:sun-clock"
    //          },

    cerr << get_icons.dump(2) << endl;

    for (auto [platform, data] : get_icons["result"]["resources"].items()) {
      // FIXME: this if skips a lot
      if (data.count("sensor")) {
        for (auto& [key, data2] : data["sensor"].items()) {
          // key: next_dawn, data2: "default": " ... ""
          auto icon = data2.value("default", "");
          if (!icon.empty()) {
            // platform: sun, key: next_dawn, icon: mdi-sun-clock
            voorkant::lvgl::iconmap[{platform, key}] = icon;
            cerr << "set iconmap[" << platform << "," << key << "]=" << icon << endl;
          }
        }
      }
    }

    json get_icons_component_req;
    get_icons_component_req["category"] = "entity_component";

    voorkant::lvgl::iconcomponentmap = ha.doCommand("frontend/get_icons", get_icons_component_req)["result"]["resources"];
  }

  if (program.is_subcommand_used(entity_command)) {
    // FIXME: does this actually need unique_ptr? I guess it might save some copying

    using MakeUIElementType = std::unique_ptr<UIEntity> (*)(std::shared_ptr<HAEntity>, lv_obj_t*);

    std::map<EntityType, MakeUIElementType> make_element_map{
      {EntityType::Light, makeUIElement<UIRGBLight>},
      {EntityType::Switch, makeUIElement<UISwitch>},
      {EntityType::Fan, makeUIElement<UIButton>},
      {EntityType::Sensor, makeUIElement<UISensor>},
      {EntityType::OTHER, makeUIElement<UISensor>}};

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

    static auto tabview = lv_tabview_create(cont_row);

    lv_obj_add_style(tabview, &voorkant::lvgl::b612style, 0); // FIXME: this should not be necessary?
    lv_obj_remove_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* tab_bar = lv_tabview_get_tab_bar(tabview);
    lv_obj_set_width(tab_bar, LV_PCT(80)); // FIXME: if you set this to 100, or remove the entire line, the tabbar renders wrong until it gets touched. Sometimes also happens at 80....

    // FIXME: don't use a tab bar at all if there is exactly one view?
    for (auto view : result["views"]) {
      uint32_t idx = lv_obj_get_child_count(lv_tabview_get_tab_bar(tabview));

      auto title = view["title"].get<std::string>();
      auto tab = lv_tabview_add_tab(tabview, title.c_str());

      lv_obj_t* button = lv_obj_get_child_by_type(tab_bar, idx, &lv_button_class);
      lv_obj_set_flex_grow(button, 0);
      lv_obj_set_width(button, LV_SIZE_CONTENT);
      lv_obj_t* label = lv_obj_get_child_by_type(button, 0, &lv_label_class);
      lv_obj_set_style_margin_hor(label, 10, 0);

      if (view.count("icon")) {
        // next couple of lines taken from lg_tabview.c lv_tabview_rename_tab, suggesting that an accessor is missing
        lv_label_set_text(label, voorkant::mdi::name2id(view["icon"].get<std::string>().substr(4)).data());
        lv_obj_add_style(label, &voorkant::lvgl::mdistyle, 0);
      }
      viewtabs.push_back(tab);
      lv_obj_remove_style_all(tab);
      lv_obj_set_size(tab, lv_pct(100), lv_pct(100));
      lv_obj_set_flex_flow(tab, LV_FLEX_FLOW_ROW);
      lv_obj_set_style_pad_row(tab, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_pad_column(tab, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_scroll_snap_x(tab, LV_SCROLL_SNAP_START);
      lv_obj_remove_flag(tab, LV_OBJ_FLAG_SCROLLABLE);

      if (view.contains("sections")) {
        for (auto section : view["sections"]) {
          renderSection(uielements, section, tab);
        }
      }
      else {
        // if we get here, this was not a Sections view, and we dumbly assume it's a masonry view, holding cards
        // FIXME: which we then all render vertically as if they are in one section, which is not pretty
        // need to check whether type 3 (Panel) and 4 (Sidebar) from https://www.home-assistant.io/dashboards/views/ do anything sensible here
        renderSection(uielements, view, tab);
      }
    }

    // FIXME: nothing about the way this clock is put on the screen makes me happy. I want it to be part of tab_bar, flushed to the right
    clocklabel = lv_label_create(lv_screen_active());
    lv_obj_set_align(clocklabel, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(clocklabel, "13:37");
    voorkant::lvgl::b612fontbig = lv_tiny_ttf_create_data_ex(B612_Regular_ttf, B612_Regular_ttf_len, 32, LV_FONT_KERNING_NORMAL, 1024);
    lv_style_init(&voorkant::lvgl::b612stylebig);
    lv_style_set_text_font(&voorkant::lvgl::b612stylebig, voorkant::lvgl::b612fontbig);
    lv_obj_add_style(clocklabel, &voorkant::lvgl::b612stylebig, 0);
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
      // FIXME: we don't need to update the clock every 5ms
      auto t = std::time(nullptr);
      auto tm = *std::localtime(&t);
      std::ostringstream time;
      time << std::put_time(&tm, "%H:%M:%S");
      lv_label_set_text(clocklabel, time.str().c_str());
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

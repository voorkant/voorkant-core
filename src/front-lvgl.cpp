#include "front-lvgl.hpp"
#include "HAEntity.hpp"
#include "uicomponents/UIComponents.hpp"

std::mutex g_lvgl_updatelock;

template<typename UIType>
void addElement(std::vector<std::unique_ptr<UIEntity>> &_uielements, std::shared_ptr<HAEntity> _entity, lv_obj_t* _contRow) {
  std::unique_ptr<UIEntity> xentity = std::make_unique<UIType>(_entity, _contRow);
    _uielements.push_back(std::move(xentity));
}

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

// make sure these numbers align with SDL_HOR_RES/SDL_VER_RES
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480
#define DISP_BUF_SIZE 16384

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

  /*Create a container with ROW flex direction that wraps.
  This is our MAIN box that we put everything in. We have this here because we want some spacing around it.
  */
  lv_obj_t* cont_row = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(cont_row);
  lv_obj_set_size(cont_row, MY_DISP_HOR_RES, MY_DISP_VER_RES);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_COLUMN_WRAP);
  lv_obj_set_style_pad_row(cont_row, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(cont_row, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

  std::vector<std::unique_ptr<UIEntity>> uielements;

  using AddElementType = void (*)(std::vector<std::unique_ptr<UIEntity>> &, std::shared_ptr<HAEntity>, lv_obj_t*);

  std::map<EntityType, AddElementType> add_element_map{
    {EntityType::Light, addElement<UIRGBLight>},
    {EntityType::Switch, addElement<UISwitch>},
    {EntityType::Fan, addElement<UIButton>},
    {EntityType::OTHER, addElement<UIDummy>}};

  auto entities = _backend.getEntitiesByPattern(entity_command.get<string>("pattern"));
  std::cerr << "Entities are: " << entities.size() << std::endl;
  for (const auto& entity : entities) {
    // FIXME: this is very simple and should move to something with panels in HA.
    add_element_map[entity->getEntityType()](uielements, entity, cont_row);
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
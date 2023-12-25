#include "main.hpp"

#include "argparse.hpp"
#include "src/argparse.hpp"

#include <iostream>
#include <sdl/sdl_common.h>
#include <string>
#include <unistd.h>

#include <lvgl.h>
#include <src/core/lv_disp.h>
#include "sdl/sdl.h"

using std::string;
// using std::map;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;

static uint32_t c=0;
void uithread(WSConn & /* wc */, int argc, char* argv[])
{
    cerr<<"calling lv_init"<<endl;
    lv_init();
    sdl_init();
    cerr<<"called lv_init and sdl_init"<<endl;

#define MY_DISP_HOR_RES 480
    /*Create a display buffer*/
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf_1[MY_DISP_HOR_RES * 10];
    static lv_color_t buf_2[MY_DISP_HOR_RES * 10];
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES*10);

    lv_disp_drv_t disp_drv;                 /*A variable to hold the drivers. Can be local variable*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;            /*Set an initialized buffer*/
    disp_drv.flush_cb = sdl_display_flush;        /*Set a flush callback to draw to the display*/
    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    argparse::ArgumentParser program("client-cli");

    argparse::ArgumentParser subscribe_command("subscribe");
    subscribe_command.add_argument("pattern")
      .help("specific state name, or *"); // maybe .remaining() so you can subscribe multiple?

    program.add_subparser(subscribe_command);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        cerr << err.what() << endl;
        cerr << program;
        return;
    }

    if (program.is_subcommand_used(subscribe_command)) {
        // FIXME: now actually use the argument
        cerr << "should subscribe to " << subscribe_command.get<string>("pattern") << endl;
    }
    else {
        cerr << "no command given" << endl;
    }


    while(true) {
        // uint32_t c = rand();
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(c), LV_PART_MAIN);
        sleep(1);
        lv_tick_inc(1000);
        lv_task_handler();
        cerr<<"."<<flush;
    }
}

void uithread_refresh(std::vector<std::string> whatchanged) // would be cool if this got told what changed
{
    // return;
    std::scoped_lock lk(entrieslock, stateslock, domainslock);

    cerr<<whatchanged.size()<<endl;
    for(const auto &changed : whatchanged) {
        cout<<"state for "<<changed<<" is "<<states[changed]->getInfo()<<endl;
        auto attrs = states[changed]->getJsonState()["attributes"];
        cout<<attrs<<endl;
        if(attrs.count("rgb_color")) {
            auto rgb = attrs["rgb_color"];
            cout<<"RGB "<<rgb;
            uint32_t color = (rgb[0].get<int>() << 16) + (rgb[1].get<int>() << 8) + (rgb[2].get<int>());
            cout<<" "<<color;
            c=color;
        }
        for(const auto &attr : states[changed]->attrVector()) {
            cout<<"  " << attr <<endl;
        }
    }
}
#include "main.hpp"

#include "argparse.hpp"
#include "src/argparse.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

#include <lvgl.h>
#include "sdl/sdl.h"

using std::string;
// using std::map;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;

void uithread(WSConn & /* wc */, int argc, char* argv[])
{
    cerr<<"calling lv_init"<<endl;
    lv_init();
    sdl_init();
    cerr<<"called lv_init"<<endl;


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
        for(const auto &attr : states[changed]->attrVector()) {
            cout<<"  " << attr <<endl;
        }
    }
}
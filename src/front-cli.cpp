#include "main.hpp"

#include "argparse.hpp"
#include "src/argparse.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
// using std::map;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;

void uithread(WSConn & /* wc */, int argc, char* argv[])
{
    argparse::ArgumentParser program("client-cli");

    argparse::ArgumentParser subscribe_command("subscribe");
    subscribe_command.add_argument("pattern")
      .help("specific state name, or *");

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
        cerr<<"."<<flush;
    }
}

void uithread_refresh()
{
    std::scoped_lock lk(entrieslock, stateslock, domainslock);

    for(const auto &entry : entries) {
        cout<<"entry: "<<entry<<endl;
    }
    for(const auto &[k,v] : states) {
        cout<<"state for "<<k<<" is "<<v->getInfo()<<endl;
    }
}
#include "main.hpp"

#include "argparse.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

#include "Backend.hpp"

using std::string;

using std::cerr;
using std::cout;
using std::endl;
using std::flush;

static bool uithread_refresh_print_updates = false;

void uithread(HABackend& backend, int argc, char* argv[])
{
  argparse::ArgumentParser program("client-cli");
  argparse::ArgumentParser subscribe_command("subscribe");
  subscribe_command.add_argument("pattern")
    .help("specific state name, or *"); // maybe .remaining() so you can subscribe multiple?

  program.add_subparser(subscribe_command);

  argparse::ArgumentParser token_command("ha-get-token");
  token_command.add_argument("name").help("Name of the token").default_value("voorkant");
  program.add_subparser(token_command);

  argparse::ArgumentParser list_entities_command("list-entities");
  program.add_subparser(list_entities_command);

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
    cout << "should subscribe to " << subscribe_command.get<string>("pattern") << endl;
    uithread_refresh_print_updates = true;
    backend.Start();
    cout << "Backend thread started..." << endl;
    while (true) {
      sleep(1);
      cerr << "." << flush;
    }
  }
  else if (program.is_subcommand_used(token_command)) {
    string token = backend.CreateLongToken(token_command.get<string>("name"));
    cout << token << endl;
  }
  else if (program.is_subcommand_used(list_entities_command)) {
    backend.Start();
    sleep(1); // hack, should find out if the backend really got populated
    for (const auto& entity : backend.GetEntries()) {
      cout << entity << endl;
    }
  }
  else {
    cerr << "no command given" << endl;
  }
}

void uithread_refresh(HABackend* backend, std::vector<std::string> whatchanged)
{
  if (uithread_refresh_print_updates) {
    for (const auto& changed : whatchanged) {
      auto state = backend->GetState(changed);
      cout << "state for " << changed << " is " << state->getInfo() << endl;
      for (const auto& attr : state->attrVector()) {
        cout << "  " << attr << endl;
      }
    }
  }
}

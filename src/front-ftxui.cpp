#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
// #include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "main.hpp"

#include "Backend.hpp"
#include "ext/magic_enum/include/magic_enum/magic_enum_all.hpp"

#include <string>

using std::map;
using std::string;

ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();

void uithread(HABackend& backend, int /* argc */, char*[] /* argv[] */)
{

  using namespace ftxui;

  backend.Start();

  int selected;
  int selected2;
  int selectedbutton;

  std::vector<std::string> entries2;
  entries2.push_back("hoi");
  entries2.push_back("hoi2");

  std::vector<std::string> entries;

  auto radiobox = Menu(&entries, &selected);
  auto radiobox2 = Menu(&entries2, &selected2);

  auto uirenderer = Container::Horizontal({});

  string pressed;

  auto renderer = Renderer(uirenderer, [&] {
    // std::scoped_lock lk(entrieslock, stateslock, domainslock);

    entries = backend.GetEntries();
    // for(auto &[k,v] : domains) {
    //   cerr<<"domain "<<k<<"exists"<<endl;
    // }
    std::vector<std::shared_ptr<HAService>> services;
    // cerr<<"about to get services, selected=="<<selected<<" , entries.size=="<<entries.size()<<endl;
    if (selected >= 0 && entries.size() > 0) {
      // cerr<<"getting services"<<endl;
      services = backend.GetServicesForDomain(backend.GetState(entries.at(selected))->domain);
    }

    std::vector<Component> buttons;
    for (const auto& service : services) {
      auto entity = entries.at(selected);

      // cerr<<service<<endl;
      buttons.push_back(Button(service->name, [&selected, &backend, &entries, service] {
        // cout<<"PUSHED: "<< entries.at(selected) << service<<endl;

        json cmd;

        cmd["type"] = "call_service";
        cmd["domain"] = backend.GetState(entries.at(selected))->domain;
        cmd["service"] = service->name;
        cmd["target"]["entity_id"] = entries.at(selected);

        backend.WSConnSend(cmd);
      })); // FIXME: this use of entries.at is gross, should centralise the empty-entries-list fallback
    }

    // cerr<<"services.size()=="<<services.size()<<", buttons.size()=="<<buttons.size()<<endl;

    uirenderer->DetachAllChildren();
    uirenderer->Add(radiobox | vscroll_indicator | frame | /* size(HEIGHT, LESS_THAN, 15) | */ size(WIDTH, EQUAL, 60) | border);
    // if (selected >= 0 && entries.size() > 0)
    if (!buttons.empty()) {
      auto buttonrenderer = Container::Vertical(buttons, &selectedbutton);
      uirenderer->Add(buttonrenderer | size(WIDTH, GREATER_THAN, 15));
    }

    std::vector<Element> attrs;
    if (selected >= 0 && entries.size() > 0) {
      for (const auto& attr : backend.GetState(entries.at(selected))->attrVector()) {
        attrs.push_back(text(attr));
      }
    }

    return vbox(
      hbox(text("selected = "), text(selected >= 0 && entries.size() ? entries.at(selected) : "")),
      text(selected >= 0 && entries.size() > 0 ? backend.GetState(entries.at(selected))->getInfo() : "no info"),
      text(pressed),
      // text("hi"),
      // hbox(text("selected2 = "), text(selected2 >=0 && entries2.size() ? entries2.at(selected2) : "")),
      // vbox(
      // {
      // hbox(
      //   {
      //     // text("test") | border,
      //     // paragraph(selected >= 0 && domains.size()>0 ? domains.at(states.at(entries.at(selected))->getDomain())->getServices()[0] : "")
      //     // paragraph(selected >= 0 && entries.size() > 0 ? getServicesForDomain(states.at(entries.at(selected))->getDomain() )[0] : "")
      //   }
      // ),
      hbox({uirenderer->Render(),
            vbox(attrs)})
      // }
      // )
    );
  });

  renderer |= CatchEvent([&](Event event) {
    if (event.is_character()) {
      auto c = event.character();

      if (c == "q") {
        screen.ExitLoopClosure()(); // FIXME: surely this can be cleaner
      }

      pressed += event.character();
    }
    return false;
  });
  // auto screen = ScreenInteractive::FitComponent();
  screen.Loop(renderer);
}

void uithread_refresh(HABackend* /* backend */, std::vector<std::string> /* whatchanged */)
{
  screen.PostEvent(ftxui::Event::Custom); // REMOVE
}
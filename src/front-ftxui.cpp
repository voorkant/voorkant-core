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

using std::string;

ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::FitComponent();

void uithread(int /* argc */, char*[] /* argv[] */)
{

  using namespace ftxui;

  HABackend::GetInstance().start();

  int selected = 0;
  int selectedbutton;

  std::vector<std::string> entries;

  auto radiobox = Menu(&entries, &selected);

  auto uirenderer = Container::Horizontal({});

  string pressed;

  auto renderer = Renderer(uirenderer, [&] {
    // std::scoped_lock lk(entrieslock, stateslock, domainslock);

    auto entities = HABackend::GetInstance().getEntities();
    entries.clear();
    for (auto& [name, entity] : entities) {
      entries.push_back(name);
    }

    std::vector<std::shared_ptr<HAService>> services;
    // cerr<<"about to get services, selected=="<<selected<<" , entries.size=="<<entries.size()<<endl;
    if (selected >= 0 && entries.size() > 0) {
      string entity = entries.at(selected);
      std::shared_ptr<HAEntity> haent = HABackend::GetInstance().getEntityByName(entity);
      services = haent->getServices();
    }

    std::vector<Component> buttons;
    for (const auto& service : services) {
      auto entity = entries.at(selected);

      // cerr<<service<<endl;
      buttons.push_back(Button(service->name, [&selected, &entries, service] {
        // cout<<"PUSHED: "<< entries.at(selected) << service<<endl;

        json cmd;

        cmd["type"] = "call_service";
        cmd["domain"] = HABackend::GetInstance().getEntityByName(entries.at(selected))->domain;
        cmd["service"] = service->name;
        cmd["target"]["entity_id"] = entries.at(selected);

        HABackend::GetInstance().wsConnSend(cmd);
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
      for (const auto& attr : HABackend::GetInstance().getEntityByName(entries.at(selected))->attrVector()) {
        attrs.push_back(text(attr));
      }
    }

    return vbox(
      hbox(text("selected = "), text(selected >= 0 && entries.size() ? entries.at(selected) : "")),
      text(selected >= 0 && entries.size() > 0 ? HABackend::GetInstance().getEntityByName(entries.at(selected))->getInfo() : "no info"),
      text(pressed),
      hbox({uirenderer->Render(), vbox(attrs)}));
  });

  renderer |= CatchEvent([&](Event _event) {
    if (_event.is_character()) {
      auto c = _event.character();

      if (c == "q") {
        screen.ExitLoopClosure()(); // FIXME: surely this can be cleaner
      }

      pressed += _event.character();
    }
    return false;
  });
  // auto screen = ScreenInteractive::FitComponent();
  screen.Loop(renderer);
}

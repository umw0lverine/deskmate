#ifndef DESKMATE_APP_APP_H
#define DESKMATE_APP_APP_H

#include <iostream>
#include <memory>
#include <vector>

#include "deskmate/app/config.h"
// #include "deskmate/gfx/components/mqtt_list_item.h"
// #include "deskmate/gfx/components/text_list_item.h"
#include "deskmate/gfx/display.h"
// #include "deskmate/gfx/screens/list.h"
#include "deskmate/gfx/screens/window.h"
#include "deskmate/input/input.h"
#include "deskmate/mqtt/mqtt.h"

namespace deskmate {
namespace app {
namespace {

using deskmate::app::MQTTConfig;
using deskmate::gfx::Display;
// using deskmate::gfx::Size;
// using deskmate::gfx::components::MQTTListItem;
// using deskmate::gfx::components::TextListItem;
// using deskmate::gfx::screens::ListItem;
// using deskmate::gfx::screens::ListScreen;
// using deskmate::gfx::screens::Window;
// using deskmate::gfx::screens::WindowedScreen;
// using deskmate::input::InputEventHandler;
// using deskmate::mqtt::MQTTMessage;
// using deskmate::mqtt::MQTTMessageBuffer;
// using deskmate::mqtt::MQTTSubscriber;

}  // namespace

// TODO: make this more flexible. In an ideal world, it would receive a config
// file and would instantiate an app to match it. Right now the definitions of
// which screens, items are used are hardcoded, and the configs only control
// which items are present.
// Clients of this class should be able to instantiate any combination of
// screen/items they want.
class App {
 public:
  App(Display *display, deskmate::mqtt::MQTTMessageBuffer *mqtt_buffer)
      : display_(display), mqtt_buffer_(mqtt_buffer) {}

  bool Init(const std::vector<MQTTConfig> &mqtt_configs);

  bool Tick();

  deskmate::input::InputEventHandler *GetInputEventHandler() {
    return window_.get();
  }

 private:
  Display *display_;
  deskmate::mqtt::MQTTMessageBuffer *mqtt_buffer_;
  std::unique_ptr<deskmate::gfx::screens::Window> window_;
  std::vector<deskmate::mqtt::MQTTSubscriber *> mqtt_subscribers_;
};

}  // namespace app
}  // namespace deskmate

#endif  // DESKMATE_APP_APP_H
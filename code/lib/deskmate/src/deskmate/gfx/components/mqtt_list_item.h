#ifndef DESKMATE_GFX_COMPONENTS_MQTT_LIST_ITEM_H
#define DESKMATE_GFX_COMPONENTS_MQTT_LIST_ITEM_H

#include "deskmate/gfx/display.h"
#include "deskmate/gfx/screens/list.h"
#include "deskmate/mqtt/mqtt.h"

namespace deskmate {
namespace gfx {
namespace components {

// Represents a ListItem that issues MQTT messages when clicked and listens and
// reacts to a topic.
class MQTTListItem : public deskmate::gfx::screens::ListItem,
                     public deskmate::mqtt::MQTTSubscriber {
 public:
  MQTTListItem(const std::string& display_name,
               const std::string& command_topic,
               const std::string& subscription_topic,
               deskmate::mqtt::MQTTMessageQueue* mqtt_out_queue);

  void Render(deskmate::gfx::Display* display, bool is_selected) const override;

  void OnSelect() override;

  std::string GetSubscriptionTopic() const override;

 private:
  void HandleOwnMessage(const deskmate::mqtt::MQTTMessage& msg) override;

  std::string display_name_;
  std::string command_topic_;
  std::string subscription_topic_;
  deskmate::mqtt::MQTTMessageQueue* mqtt_out_queue_;
  bool on_ = false;
};

}  // namespace components
}  // namespace gfx
}  // namespace deskmate

#endif  // DESKMATE_GFX_COMPONENTS_MQTT_LIST_ITEM_H
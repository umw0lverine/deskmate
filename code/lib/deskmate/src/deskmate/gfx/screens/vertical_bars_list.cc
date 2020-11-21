#include "deskmate/gfx/screens/vertical_bars_list.h"

#include <algorithm>

#include "deskmate/gfx/constants.h"
#include "deskmate/gfx/display.h"
#include "deskmate/input/input.h"

namespace deskmate {
namespace gfx {
namespace screens {

namespace {
using deskmate::gfx::Color;
using deskmate::gfx::Rect;
using deskmate::gfx::Size;
using deskmate::gfx::constants::kPadding;
using deskmate::input::InputEvent;

// Radius for the little circle that is drawn under the currently selected bar.
constexpr unsigned int kSelectorRadius = 8;
}  // namespace

VerticalBarsList::~VerticalBarsList() = default;

// TODO: handle horizontal scroll.
void VerticalBarsList::HandleInputEvent(InputEvent event) {
  switch (event) {
    case InputEvent::kCrankCW:
      selected_ = selected_ < items_.size() - 1 ? selected_ + 1 : selected_;
      break;
    case InputEvent::kCrankCCW:
      selected_ = selected_ > 0 ? selected_ - 1 : 0;
      break;
    case InputEvent::kAPush:
      items_[selected_]->OnSelect();
      break;
    default:
      break;
  }
}

void VerticalBarsList::Render(Display* display) const {
  uint8_t font_scale = 2;
  const Size& window_size = display->GetSize();
  display->PushWindow({{kPadding, kPadding},
                       {window_size.height, window_size.width - 2 * kPadding}});

  const Size& inner_size = display->GetSize();
  const unsigned int text_height =
      2 * kPadding + font_scale * display->GetCharSize().height;
  const unsigned int selector_height = 2 * kPadding + 2 * kSelectorRadius;
  const unsigned int divider_height = 1;
  const unsigned int top_bars_y = 0;
  const unsigned int bottom_bars_y =
      inner_size.height - text_height - selector_height - divider_height;

  const unsigned int offset_x = kPadding;
  // TODO: better automatic layout. Ideas:
  // * Center bars
  // * Automatically set bars widths
  Rect bar_rect;
  bar_rect.size.width = 2 * kPadding;
  for (int i = 0; i < items_.size(); i++) {
    bar_rect.point.x = offset_x + i * 2 * bar_rect.size.width;
    unsigned int percentage_in_pixels =
        items_[i]->Percentage() * (bottom_bars_y - top_bars_y);
    bar_rect.point.y = bottom_bars_y - percentage_in_pixels;
    // +1 to ensure it aligns nicely with the divider.
    bar_rect.size.height = percentage_in_pixels + 1;
    if (items_[i]->IsFilled()) {
      display->FillRect(bar_rect, Color::kBlack);
    } else {
      display->DrawRect(bar_rect, Color::kBlack);
    }

    if (i == selected_) {
      Point selector_center{
          bottom_bars_y + divider_height + kPadding + kSelectorRadius,
          bar_rect.point.x + bar_rect.size.width / 2,
      };
      display->FillCircle(selector_center, kSelectorRadius, Color::kBlack);
    }
  }

  Rect divider_rect{{bottom_bars_y, 0}, {divider_height, inner_size.width}};
  display->DrawRect(divider_rect, Color::kBlack);

  // Name.
  // TODO: ellipsis if name is too long.
  display->PutText(
      divider_rect.point.y + divider_rect.size.height + selector_height, 0,
      items_[selected_]->DisplayName(), font_scale, Color::kBlack);

  // Percentage.
  int percentage = 100 * items_[selected_]->Percentage();
  const std::string percentage_str = std::to_string(percentage) + "%";
  display->PutText(
      divider_rect.point.y + divider_rect.size.height + selector_height,
      inner_size.width - percentage_str.length() * font_scale * display->GetCharSize().width,
      percentage_str, font_scale, Color::kBlack);

  // Pop the padded window.
  display->PopWindow();
}

}  // namespace screens
}  // namespace gfx
}  // namespace deskmate
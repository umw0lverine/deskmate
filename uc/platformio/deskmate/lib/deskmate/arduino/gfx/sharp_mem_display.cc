#include <memory>
#include <string>

#include <Adafruit_SharpMem.h>

#include "deskmate/arduino/gfx/sharp_mem_display.h"

namespace deskmate {
namespace arduino {
namespace gfx {

SharpMemDisplay::SharpMemDisplay(unsigned int height, unsigned int width, uint8_t sck_pin, uint8_t mosi_pin, uint8_t cs_pin):
    height_(height),
    width_(width),
    display_(std::make_unique<Adafruit_SharpMem>(sck_pin, mosi_pin, cs_pin, width, height)) {
  display_->begin();
  display_->clearDisplay();
  display_->cp437(true);
}

SharpMemDisplay::~SharpMemDisplay() {
}

void SharpMemDisplay::Clear() {
  display_->clearDisplay();
}

void SharpMemDisplay::Refresh() {
  display_->refresh();
}

void SharpMemDisplay::DrawPixel(int y, int x, bool white) {
  display_->drawPixel(x, y, white ? 1 : 0);
}

void SharpMemDisplay::PutText(int y, int x, const std::string& text, int size, bool white) {
  display_->setTextColor(white ? 1 : 0);
  display_->setTextSize(size);
  display_->setCursor(x, y);
  display_->write(text.c_str());
}

}  // namespace gfx
}  // namespace arduino
}  // namespace deskmate
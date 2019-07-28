#include "MCUFRIEND_Panel.h"

void Panel::setTft(MCUFRIEND_kbv * tft) {
  this->tft = tft;
}

void Panel::setup(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height, uint8_t cornerRadius, uint16_t bgColor) {
  this->xLoc = xLoc;
  this->yLoc = yLoc;
  this->height = height;
  this->width = width;
  this->cornerRadius = cornerRadius;
  this->bgColor = bgColor;
}

void Panel::render() {
  if (tft == NULL) {
    return;
  }
  if (cornerRadius > 0) {
    tft->fillRoundRect(xLoc, yLoc, width, height, cornerRadius, bgColor);
  } else {
    tft->drawRect(xLoc, yLoc, width, height, bgColor);
  }
  renderContent();
}

void Panel::renderContent() {
  if (tft == NULL) {
    return;
  }
  renderContentWithin(xLoc + cornerRadius, yLoc + cornerRadius, width - 2 * cornerRadius, height - 2 * cornerRadius);
}

void Panel::renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height) {
}


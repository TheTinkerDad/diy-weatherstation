#ifndef MCUFRIEND_PANEL_H_
#define MCUFRIEND_PANEL_H_

#include <MCUFRIEND_kbv.h>

class Panel {
  public:
    void setTft(MCUFRIEND_kbv * tft);
    void setup(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height, uint8_t cornerRadius, uint16_t bgColor);
    void render();
    void renderContent();
  protected:
    MCUFRIEND_kbv * tft;
    
    virtual void renderContentWithin(uint16_t xLoc, uint16_t yLoc, uint16_t width, uint16_t height);
  private:
    uint16_t xLoc;
    uint16_t yLoc;
    uint16_t height;
    uint16_t width;
    uint8_t cornerRadius;
    uint16_t bgColor;
};

#endif

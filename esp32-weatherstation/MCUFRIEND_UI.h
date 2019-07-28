#ifndef MCUFRIEND_UI_H_
#define MCUFRIEND_UI_H_

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <iterator>
#include <vector>

#include "MCUFRIEND_Panel.h"

#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF

#define ORANGE      0xFD80
#define DARK_GREEN  0x0400
#define METAL_BLUE  0x0CB7
#define PALE_RED    0xF9E7

class UI {
  public:
    UI(MCUFRIEND_kbv * tft);
    void setup();
    void add(Panel * panel);
    void render();
    void renderContent();
  private:
    MCUFRIEND_kbv * tft;
    std::vector<Panel*> panels;
};

#endif

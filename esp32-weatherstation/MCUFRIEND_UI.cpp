#include "MCUFRIEND_UI.h"

UI::UI(MCUFRIEND_kbv * tft) {
  this->tft = tft;
}

void UI::setup() {
  uint16_t ID = tft->readID();
  if (ID == 0xD3D3) ID = 0x9481;
  tft->begin(ID);
  tft->setRotation(-1);
  tft->fillScreen(BLACK);
  tft->setTextSize(2);
}

void UI::add(Panel * panel) {
  panel->setTft(tft);
  this->panels.push_back(panel);
}

void UI::render() {
  for (int i = 0; i < panels.size(); i++){
    this->panels[i]->render();
  }
}

void UI::renderContent() {
  for (int i = 0; i < panels.size(); i++){
    this->panels[i]->renderContent();
  }
}



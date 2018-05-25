#ifndef GUI_H
#define GUI_H

#include "Model.h"

class Gui : public Model {
public:  
  string bttn_image;
  Gui(float X, float Y, string bttn_image)
      : Model(bttn_image) {
    model_sprite.setPosition(X, Y);    
  }
};

#endif

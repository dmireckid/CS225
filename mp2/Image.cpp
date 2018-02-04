#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>
#include "Image.h"

using namespace cs225;

void Image:: lighten(){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      pix.l = fmin(1.0, pix.l + 0.1);
    }
  }
}

void Image:: lighten(double amount){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      pix.l = fmin(1.0, pix.l + amount);
    }
  }
}

void Image:: darken(){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      pix.l = fmax(0.0, pix.l - 0.1);
    }
  }
}

void Image:: darken(double amount){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      pix.l = fmax(0.0, pix.l - amount);
    }
  }
}

void Image:: saturate(){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
        HSLAPixel & pix = this->getPixel(i,j);
        pix.s = fmin(1.0, pix.s + 0.1);
    }
  }
}

void Image:: saturate(double amount){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
        HSLAPixel & pix = this->getPixel(i,j);
        pix.s = fmin(1.0, pix.s + amount);
    }
  }
}

void Image:: desaturate(){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
        HSLAPixel & pix = this->getPixel(i,j);
        pix.s = fmax(0.0, pix.s - 0.1);
    }
  }
}

void Image:: desaturate(double amount){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
        HSLAPixel & pix = this->getPixel(i,j);
        pix.s = fmax(0.0, pix.s - amount);
    }
  }
}

void Image:: grayscale(){
  for(unsigned i=0; i<this->width(); i++){
    for(unsigned j=0; j<this->height(); j++){
        HSLAPixel & pix = this->getPixel(i,j);
        pix.s = 0.0;
    }
  }
}

void Image:: rotateColor(double degrees){
  for(double i=0; i<this->width(); i++){
    for(double j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      if(pix.h + degrees > 360)
        pix.h = pix.h + degrees - 360;
      else if(pix.h + degrees < 0)
        pix.h = pix.h + degrees + 360;
      else
        pix.h += degrees;
    }
  }
}

void Image:: illinify(){
  for(double i=0; i<this->width(); i++){
    for(double j=0; j<this->height(); j++){
      HSLAPixel & pix = this->getPixel(i,j);
      if(pix.h > 113.5 && pix.h < 293.5)
        pix.h = 216;
      else
        pix.h =11;
    }
  }
}

void Image:: scale(double factor){

}

void Image:: scale(unsigned w, unsigned h){
  HSLAPixel * newImageData = new HSLAPixel[w * h];

  // Copy the current data to the new image data, using the existing pixel
  // for coordinates within the bounds of the old image size
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      if (x < this->width() && y < this->height()) {
        HSLAPixel & oldPixel = this->getPixel(x, y);
        HSLAPixel & newPixel = newImageData[ (x + (y * w)) ];
        newPixel = oldPixel;
      }
    }
  }

  // Clear the existing image
  delete[] imageData_;

  // Update the image to reflect the new image size and data
  width_ = w;
  height_ = h;
  imageData_ = newImageData;
}

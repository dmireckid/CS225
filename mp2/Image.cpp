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
  int neww = (this->width())*factor;
  int newh = (this->height())*factor;
  if(factor>1){
    this->resize(neww, newh);
    for(int i=neww-1; i>=0; i--){
      for(int j=newh-1; j>=0; j--){

        HSLAPixel& pix=this->getPixel(i,j);
        HSLAPixel& pix2=this->getPixel(i/factor, j/factor);
        pix=pix2;

      }
    }
    //this->resize(neww, newh);
  }
  else if(factor<1){
    //this->resize(neww, newh);
    for(int i=0; i<neww; i++){
      for(int j=0; j<newh; j++){

        HSLAPixel& pix=this->getPixel(i,j);
        HSLAPixel& pix2=this->getPixel(i/factor, j/factor);
        pix=pix2;

      }
    }
    this->resize(neww, newh);
  }
}

void Image:: scale(unsigned w, unsigned h){
  double factor;
  if((w/this->width()) > (h/this->height())){
    factor = (h/this->height());
  }
  else{
    factor = (w/this->width());
  }
  this->scale(factor);
}

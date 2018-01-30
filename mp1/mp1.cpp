#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  PNG * in = new PNG();
  in->readFromFile(inputFile);
  unsigned int w = in->width();
  unsigned int h = in->height();
  PNG * out = new PNG(w, h);

  for(unsigned int i=0; i<w; i++){
    for(unsigned int j=0; j<h; j++){
      HSLAPixel* ip = in->getPixel(i, j);
      HSLAPixel* ipr = in->getPixel(w-i-1, h-j-1);
      HSLAPixel* op = out->getPixel(w-i-1, h-j-1);
      HSLAPixel* opr = out->getPixel(i, j);
      *op = *ip;
      *opr = *ipr;
    }
  }
  out->writeToFile(outputFile);

  delete out;
  delete in;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  for(unsigned int x = 0; x < (width); x++){
    for(unsigned int y = 0; y < (height/2); y++){
      HSLAPixel *my = png.getPixel(x, y);
      my->h=120;
      my->s=1;
      my->l=0.5;
      my->a=1;
    }
  }
  for(unsigned int x = 0; x < (width); x++){
    for(unsigned int y = (height/2); y < (height); y++){
      HSLAPixel *my = png.getPixel(x, y);
      my->h=240;
      my->s=1;
      my->l=0.5;
      my->a=1;
    }
  }
  for(unsigned int x = 0; x < width; x++){
    /*for(unsigned int y = (height/2); y < (height); y++){*/
      HSLAPixel *my = png.getPixel(x, x);
      my->h=0;
      my->s=1;
      my->l=0.5;
      my->a=1;
  }
  for(unsigned int x = 0; x < width; x++){
    /*for(unsigned int y = (height/2); y < (height); y++){*/
      HSLAPixel *my = png.getPixel(x, height-x-1);
      my->h=0;
      my->s=1;
      my->l=0.5;
      my->a=1;
  }
  for(unsigned int x = 0; x < width; x++){
    /*for(unsigned int y = (height/2); y < (height); y++){*/
      HSLAPixel *my = png.getPixel(x, height/2);
      my->h=0;
      my->s=1;
      my->l=0.5;
      my->a=1;
  }
  for(unsigned int x = 0; x < width; x++){
    /*for(unsigned int y = (height/2); y < (height); y++){*/
      HSLAPixel *my = png.getPixel(width/2, x);
      my->h=0;
      my->s=1;
      my->l=0.5;
      my->a=1;
  }
  return png;
}

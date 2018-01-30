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
  /*for(unsigned int x = 0; x < (width/3); x++){
    for(unsigned int y = 0; y < (height); y++){
      png[x, y]->h=0;
      png[x, y]->s=1;
      png[x, y]->l=0.5;
      png[x, y]->a=1;
    }
  }
  for(unsigned int x = (width/3); x < (2*width/3); x++){
    for(unsigned int y = 0; y < (height); y++){
      png[x, y]->h=120;
      png[x, y]->s=1;
      png[x, y]->l=0.5;
      png[x, y]->a=1;
    }
  }
  for(unsigned int x = (2*width); x < width; x++){
    for(unsigned int y = 0; y < (height); y++){
      png[x, y]->h=240;
      png[x, y]->s=1;
      png[x, y]->l=0.5;
      png[x, y]->a=1;
    }
  }*/


  return png;
}

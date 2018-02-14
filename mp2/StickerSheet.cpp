#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  max_ = max;
  picture_ = new Image();
  *picture_ = picture;
  imArr_ = new Image* [max_];
  StickerX = new int[max_];
  StickerY = new int[max_];
  for(unsigned int i=0; i<max_; i++){
    imArr_[i] = NULL;
    StickerX[i] = 0;
    StickerY[i] = 0;
  }
  //imArr_[0]=&Image(picture)
}

StickerSheet::~StickerSheet(){
  clear();
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  if(this != &other){
    clear();
    copy(other);
  }
  return * this;
}

void StickerSheet::changeMaxStickers(unsigned max){
  if(max_ > max){
    for(unsigned j=max-1; j<max_; j++){
      if(imArr_[j] != NULL){
        return;
      }
    }
  }
  if(max_==max){
    return;
  }
  /*else if(max_ > max){
    Image** im = new Image*[max];
    int* StickerX2 = new int [max];
    int* StickerY2 = new int [max];
    for(unsigned i=0; i<max; i++){
      im[i] = imArr_[i];
      StickerX2[i] = StickerX[i];
      StickerY2[i] = StickerY[i];
    }
    clear();
    imArr_ = im;
    StickerX = StickerX2;
    StickerY = StickerY2;
    max_=max;
  }
  else{
    Image** im = new Image*[max];
    int* StickerX2 = new int [max];
    int* StickerY2 = new int [max];
    for(unsigned i=0; i<max; i++){
      im[i] = imArr_[i];
      StickerX2[i] = StickerX[i];
      StickerY2[i] = StickerY[i];
    }
    for(unsigned i=max_-1; i<max; i++){
      im[i]=NULL;
    }
    clear();
    imArr_ = im;
    StickerX = StickerX2;
    StickerY = StickerY2;
    max_=max;
  }*/
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  Image* temp=new Image();
  *temp=sticker;
  for(unsigned int i = 0; i<max_; i++){
    if(imArr_[i] == NULL){
      imArr_[i]=temp;
      StickerX[i]=x;
      StickerY[i]=y;
      return i;
    }
  }
  delete temp;
  return 0;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index>max_ || imArr_[index]==NULL){
    return false;
  }
  else{
    StickerX[index] = x;
    StickerY[index] = y;
    return true;
  }
}

void StickerSheet::removeSticker(unsigned index){
  if(imArr_[index] != NULL){
    delete imArr_[index];
    imArr_[index]=NULL;
    //StickerY[index] = 0;
    //StickerX[index] = 0;
  }
}

Image* StickerSheet::getSticker(unsigned index) const{
  if(index<max_ && imArr_[index] != NULL){
    return imArr_[index];
  }
  else{
    return NULL;
  }
}

Image StickerSheet::render() const{
  Image *im = new Image();
  unsigned int height=picture_->height();
  unsigned int width=picture_->width();
  /*for(unsigned int a=0; a<width; a++){
    for(unsigned int b=0; b<height; b++){
      im->getPixel(a,b) = picture_->getPixel(a,b);
    }
  }*/
  for(unsigned int i = 0; i<max_; i++){
    if(imArr_[i] != NULL){
      unsigned int theight = imArr_[i]->height() + StickerY[i];
      unsigned int twidth = imArr_[i]->width() + StickerX[i];
      if(height < theight){
        height = theight;
      }
      if(width < twidth){
        width = twidth;
      }
    }
  }
  im->resize(width, height);
  for(unsigned int a=0; a<picture_->width(); a++){
    for(unsigned int b=0; b<picture_->height(); b++){
      im->getPixel(a,b) = picture_->getPixel(a,b);
    }
  }
  for(unsigned int i=0; i<max_; i++){
    if(imArr_[i] != NULL){
      for(unsigned int j=0; j<imArr_[i]->width(); j++){
        for(unsigned int k=0; k<imArr_[i]->height(); k++){
          im->getPixel(StickerX[i]+j, StickerY[i]+k) = imArr_[i]->getPixel(j,k);
        }
      }
    }
  }
  return *im;
}

void StickerSheet::clear(){
  for(unsigned int i=0; i<max_; i++){
    if(imArr_ != NULL){
      delete imArr_[i];
      imArr_[i] = NULL;
    }
  }
  delete[] imArr_;
  imArr_=NULL;
  delete[] StickerX;
  StickerX=NULL;
  delete[] StickerY;
  StickerY=NULL;
  delete picture_;
  picture_=NULL;
}

void StickerSheet::copy(const StickerSheet & copee){
  max_ = copee.max_;
  picture_ = new Image();
  imArr_ = new Image *[max_];
  StickerX = new int[max_];
  StickerY = new int[max_];
  *picture_ = *(copee.picture_);
  for(unsigned int i=0; i<max_; i++){
    imArr_[i]=NULL;
    StickerX[i]=0;
    StickerY[i]=0;
    if(copee.imArr_[i] != NULL){
      imArr_[i] = new Image;
      StickerX[i] = copee.StickerX[i];
      StickerY[i] = copee.StickerY[i];
      *imArr_[i] = *(copee.imArr_[i]);
    }
  }
  for(unsigned int j=0; j<max_; j++){
    if(copee.imArr_[j] != NULL){
      imArr_[j] = new Image;
      *imArr_[j] = *(copee.imArr_[j]);
    }
  }
}

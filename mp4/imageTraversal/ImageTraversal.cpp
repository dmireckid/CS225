#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

double ImageTraversal::getDelta(HSLAPixel & p1, HSLAPixel & p2){
  const HSLAPixel p3 = p1;
  const HSLAPixel p4 = p2;
  return calculateDelta(p3, p4);
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  blah = NULL;

}

ImageTraversal::Iterator::Iterator(ImageTraversal* imTrav){
  blah = imTrav;
  current_ = blah->start_;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  /*Point temp = this.peek();
  visited[temp.x][temp.y] = 1;
  this.pop();
  if(temp.x+1 <*/
  // blah->add(blah->pop());
  // return *this;
  if (!blah->empty()) {
    current_ = blah->pop();
    blah->visited[current_.x][current_.y] = 1;
    //blah->add(current_);
    while(!blah->empty() && blah->visited[blah->peek().x][blah->peek().y] == 1){
      //temp = blah->top();
      Point temp;
      temp = blah->pop();
    }
    blah->add(current_);
    if(blah->empty()){
      blah = NULL;
    }
    else{
      current_ = blah->peek();
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //cout << "op* wrong" << endl;
  return blah->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  /*if(blah == NULL && other.blah == NULL){
    return false;
  }
  else if(blah == NULL || other.blah == NULL){
    return true;
  }
  if(blah->peek() == other.blah->peek()){
    return false;
  }
  else{
    return true;
  }*/
  bool thisEmpty = false;
  bool otherEmpty = false;
  if(blah == NULL){
    thisEmpty = true;
  }
  if(other.blah == NULL){
    otherEmpty = true;
  }
  if(!thisEmpty){
    thisEmpty = blah->empty();
  }
  if(!otherEmpty){
    otherEmpty = other.blah->empty();
  }
  if(thisEmpty && otherEmpty){
    return false;
  }
  else if((!thisEmpty)&&(!otherEmpty)){
    return (blah != other.blah);
  }
  else{
    return true;
  }
}

ImageTraversal::ImageTraversal(){

}

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  width_ = png.width();
  height_ = png.height();
  png_ = png;
  visited = new int*[width_];
  for(unsigned int i=0; i<width_; i++){
    visited[i] = new int[height_];
    for(unsigned int j=0; j<width_; j++){
      visited[i][j] = 0;
    }
  }
  /*added = new int*[width_];
  for(unsigned int i=0; i<width_; i++){
    added[i] = new int[height_];
    for(unsigned int j=0; j<width_; j++){
      added[i][j] = 0;
    }
  }*/
  start_ = start;
  visited[start.x][start.y] = 1;
  tolerance_ = tolerance;
  DFStack.push(start_);
  //visited[start_.x][start_.y] = 1;

  //REMINDER: DELETE THE GODDAMN FUCKING VISITED ARRAY
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  //cout << "begin began" << endl;
  ImageTraversal* blah = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(blah);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  //visited[point.x][point.y] = 1;
  if((point.x+1 < width_) /*&& point.y < height_*/ && visited[point.x+1][point.y] == 0 &&
   (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x+1, point.y)) <= tolerance_)) {
    Point rightN = Point(point.x+1, point.y);
    DFStack.push(rightN);
    visited[rightN.x][rightN.y] = 1;
  }
  if((point.y+1 < height_) /*&& point.x < width_*/ && visited[point.x][point.y+1] == 0 &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y+1)) <= tolerance_)){
    Point lowerN = Point(point.x, point.y+1);
    DFStack.push(lowerN);
    visited[lowerN.x][lowerN.y] = 1;
  }
  if((point.x-1 < width_ && point.x != 0) && visited[point.x-1][point.y] == 0 &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x-1, point.y)) <= tolerance_)){
    Point leftN = Point(point.x-1, point.y);
    DFStack.push(leftN);
    visited[leftN.x][leftN.y] = 1;
  }
  if((point.y-1 < height_ && point.y != 0) && visited[point.x][point.y-1] == 0 &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y-1)) <= tolerance_)){
    Point upperN = Point(point.x, point.y-1);
    DFStack.push(upperN);
    visited[upperN.x][upperN.y] = 1;
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  // if(DFStack.empty()){
  //   return Point(-1,-1);
  // }
  // Point temp = DFStack.top();
  // while(visited[temp.x][temp.y] == 1){
  //   if(DFStack.empty()){
  //     return Point(-2,-2);
  //   }
  //   temp = DFStack.top();
  //   DFStack.pop();
  // }
  //   temp = DFStack.top();
  //   visited[temp.x][temp.y] = 1;
  //   DFStack.pop();
  //   return temp;
  /*Point temp = DFStack.top();
  while(visited[temp.x][temp.y] == 1){
    if(DFStack.empty()){
      return Point(-2,-2);
    }
    temp = DFStack.top();
    DFStack.pop();
  }
  if(!visited[temp.x][temp.y]){
    Point temp = DFStack.top();
    visited[temp.x][temp.y] = 1;
    DFStack.pop();
    return temp;
  }
  return Point(-3, -3);
  while(visited[temp.x][temp.y] == 1){
    DFStack.pop();
    temp = DFStack.top();
  }
  visited[temp.x][temp.y] = 1;
  DFStack.pop();
  return temp;*/
  Point top = DFStack.top();
  DFStack.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  //cout << "peek peeked" << endl;
  if(DFStack.empty()){
    return Point(-1,-1);
  }
  else{
    //Point temp = DFStack.top();
    //DFStack.pop();
    return DFStack.top();
  }
  //return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(DFStack.empty()){
    return true;
  }
  else{
    return false;
  }
  //return true;
}

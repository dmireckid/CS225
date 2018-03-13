#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
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
  start_ = start;
  //visited[start.x][start.y] = 1;
  tolerance_ = tolerance;
  BFSQueue.push(start_);
  visited[start_.x][start_.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal* blah = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(blah);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if( (point.x+1 < width_) && visited[point.x+1][point.y] == 0 &&
   (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x+1, point.y)) <= tolerance_)){
    Point rightN = Point(point.x+1, point.y);
    BFSQueue.push(rightN);
    visited[rightN.x][rightN.y] = 1;
  }
  if((point.y+1 < height_) && !visited[point.x][point.y+1] &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y+1)) <= tolerance_)){
    Point lowerN = Point(point.x, point.y+1);
    BFSQueue.push(lowerN);
    visited[lowerN.x][lowerN.y] = 1;
  }
  if((point.x-1 < width_ && point.x != 0) && !visited[point.x-1][point.y] &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x-1, point.y)) <= tolerance_)){
    Point leftN = Point(point.x-1, point.y);
    BFSQueue.push(leftN);
    visited[leftN.x][leftN.y] = 1;
  }
  if((point.y-1 < height_ && point.y != 0) && !visited[point.x][point.y-1] &&
  (getDelta(png_.getPixel(point.x, point.y), png_.getPixel(point.x, point.y-1)) <= tolerance_)){
    Point upperN = Point(point.x, point.y-1);
    BFSQueue.push(upperN);
    visited[upperN.x][upperN.y] = 1;
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  /*if(BFSQueue.empty()){
    return Point(-1,-1);
  }
  Point temp = BFSQueue.front();
  while(visited[temp.x][temp.y] == 1){
    if(BFSQueue.empty()){
      return Point(-2,-2);
    }
    temp = BFSQueue.front();
    BFSQueue.pop();
  }
  //else{
    temp = BFSQueue.front();
    visited[temp.x][temp.y] = 1;
    BFSQueue.pop();
    return temp;*/
    Point front = BFSQueue.front();
    BFSQueue.pop();
    return front;

  //return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(BFSQueue.empty()){
    return Point(-1,-1);
  }
  else{
    //Point temp = BFSQueue.front();
    //BFSQueue.dequeue();
    return BFSQueue.front();
  }
  //return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(BFSQueue.empty()){
    return true;
  }
  else{
    return false;
  }
  //return true;
}

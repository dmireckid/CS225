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
  visited = new int*[width_];
  for(unsigned int i=0; i<width_; i++){
    visited[i] = new int[height_];
    for(unsigned int j=0; j<width_; j++){
      visited[i][j] = 0;
    }
  }
  start_ = start;
  tolerance_ = tolerance;
  BFSQueue.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
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
  if((point.x+1 < width_) || !visited[point.x+1][point.y]){
    Point rightN = Point(point.x+1, point.y);
    BFSQueue.push(rightN);
  }
  if((point.y+1 < height_) || !visited[point.x][point.y+1]){
    Point lowerN = Point(point.x, point.y+1);
    BFSQueue.push(lowerN);
  }
  if((point.x-1 < width_ && point.x != 0) || !visited[point.x-1][point.y]){
    Point leftN = Point(point.x-1, point.y);
    BFSQueue.push(leftN);
  }
  if((point.y-1 < height_ && point.y != 0) || !visited[point.x][point.y-1]){
    Point upperN = Point(point.x, point.y-1);
    BFSQueue.push(upperN);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(BFSQueue.empty()){
    return Point(-1,-1);
  }
  else{
    Point temp = BFSQueue.front();
    visited[temp.x][temp.y] = 1;
    BFSQueue.pop();
    return temp;
  }
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

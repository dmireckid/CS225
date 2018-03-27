/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim] <= second[curDim]){
      return true;
    }
    else{
      return false;
    }
}

template <int Dim>
int KDTree<Dim>::distanceDim(const Point<Dim>& a, const Point<Dim>& b) const{
  int count = 0;
  for(int i=0; i<Dim; i++){
    count += ((a[i] - b[i]) * (a[i] - b[i]));
  }
  return count;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    int current = distanceDim(target, currentBest);
    int potendis = distanceDim(target, potential);
    if(current == potendis){
      return potential < currentBest;
    }
    else{
      return potendis < current;
    }
     //return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    points = newPoints;
    //Helper
    if(points.size() != 0){
      KDTreeCtor(0, 0, points.size()-1, points);
    }

}

template <int Dim>
void KDTree<Dim>::KDTreeCtor(int dimension, int left, int right, vector<Point<Dim>>& newPoints){
    int middle = (left + right)/2;
    if(left > right){
      return;
    }
    points[middle] = quickselect(middle, dimension, left, right, newPoints);
    //if(left < middle){
    //create a subroot?
    KDTreeNode temp = KDTreeNode(points[middle]);
    //left subtree->
    KDTreeCtor((dimension+1)%Dim, left, middle-1, newPoints);
    //RIGHT subtree->
    KDTreeCtor((dimension+1)%Dim, middle+1, right, newPoints);

    // if(left < right){
    //   return;
    // }

}

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(int middle, int dimension, int left, int right, vector<Point<Dim>>& newPoints){
  while(left<right){
    int temp = hadToWriteAGDPartitionFunction(middle, dimension, left, right, newPoints);
    if(temp == middle){
      return newPoints[temp];
    }
    else if(temp > middle){
      right = temp-1;
    }
    else{
      left = temp+1;
    }
  }

  return newPoints[left];
}

template <int Dim>
int KDTree<Dim>::hadToWriteAGDPartitionFunction(int middle, int dimension, int left, int right, vector<Point<Dim>>& newPoints){
  Point<Dim> partition = newPoints[middle];
  Point<Dim> temp = newPoints[right];
  newPoints[right] = newPoints[middle];
  newPoints[middle] = temp;
  int leftemp = left;
  for(int i=left; i<right; i++){
    if(smallerDimVal(newPoints[i], partition, dimension)){
      temp = points[leftemp];
      newPoints[leftemp] = points[i];
      newPoints[i] = temp;
      leftemp++;
    }
  }
  temp = newPoints[right];
  newPoints[right] = newPoints[leftemp];
  newPoints[leftemp] = temp;

  return leftemp;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    int right = (points.size() - 1);
    Point<Dim> temp = points[right/2];
    Point<Dim> result = findNearestNeighbor(query, 0, right, 0, temp);
    return result;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int left, int right, int dimension, const Point<Dim>& variable) const
{
    //helper :
    return Point<Dim>();
}

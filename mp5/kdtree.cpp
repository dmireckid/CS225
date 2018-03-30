/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

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
    //if(points.size() != 0){
    KDTreeCtor(0, points, root);


}

template <int Dim>
void KDTree<Dim>::KDTreeCtor(int dimension, /*int left, int right,*/ vector<Point<Dim>>& newPoints, KDTreeNode*& subroot){
    int middle = (newPoints.size() - 1)/2;

    if(!newPoints.empty()){
      size_t length = newPoints.size();
      subroot = new KDTreeNode(quickselect(middle, dimension, 0, length-1, newPoints));
      dimension = (dimension+1)%Dim;

      std::vector<Point<Dim>> vec1;
      vec1.assign(newPoints.begin(), newPoints.begin() + (length-1)/2);
      KDTreeCtor(dimension, vec1, subroot->left);
      std::vector<Point<Dim>> vec2;
      vec2.assign(newPoints.begin() + (length-1)/2 + 1, newPoints.end());
      KDTreeCtor(dimension, vec2, subroot->right);
    }
    else{
      subroot = NULL;
    }

    // if(left < right){
    //   return;
    // }

}

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(int middle, int dimension, int left, int right, vector<Point<Dim>>& newPoints){
  while(left<right){
    int temp = partition(middle, dimension, left, right, newPoints);
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
int KDTree<Dim>::partition(int middle, int dimension, int left, int right, vector<Point<Dim>>& newPoints){
  Point<Dim> partition = newPoints[middle];
  Point<Dim> temp = newPoints[right];
  newPoints[right] = newPoints[middle];
  newPoints[middle] = temp;
  int leftemp = left;
  for(int i=left; i<right; i++){
    if(smallerDimVal(newPoints[i], partition, dimension)){
      temp = newPoints[leftemp];
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

    //return findNearestNeighbor(query, root, Point<Dim>(), false, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int left, int right, int dimension, Point<Dim>& variable) const
{
// Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subroot, Point<Dim> neighbor, bool setup, int dimension) const
// {
    //helper
    //i hate subroots :)
    if(left > right){
      if(shouldReplace(query, variable, points[left])){
        variable = points[left];
      }
      return variable;
    }
    else{
      dimension++;
      dimension= dimension%Dim;
      int middle = (left + right)/2;

      if(shouldReplace(query, variable, points[middle]) == true){
        variable = points[middle];
      }

      //recurse but howww
      if(smallerDimVal(query, points[middle], dimension) == true){
        variable = findNearestNeighbor(query, left, middle-1, dimension, variable);
        int theStorm = 0,
          temp = pow((points[middle][dimension%Dim] - query[dimension%Dim]), 2);
        for(int i = 0; i<Dim; i++){
          theStorm += pow((query[i] - variable[i]), 2);
        }
        if(theStorm > temp){
          return findNearestNeighbor(query, middle+1, right, dimension, variable);
        }
      }
      else if(smallerDimVal(points[middle], query, dimension)==true){
        variable = findNearestNeighbor(query, middle+1, right, dimension, variable);
        int theStorm = 0,
          temp = pow((points[middle][dimension%Dim] - query[dimension%Dim]), 2);
        for(int i = 0; i<Dim; i++){
          theStorm += pow((query[i] - variable[i]), 2);
        }
        if(theStorm > temp){
          return findNearestNeighbor(query, left, middle-1, dimension, variable);
        }
      }
    }
    return variable;/*
    if(subroot == NULL){
      return Point<Dim>();
    }
    if(subroot->point == query){
      return query;
    }
    if((subroot->left == NULL && subroot->right == NULL) || (subroot->left == NULL && query[dimension]<subroot->point[dimension]) || (subroot->right == NULL && query[dimension]>subroot->point[dimension])){
      if(setup == false){
        neighbor = subroot->point;
      }
      if(shouldReplace(query, neighbor, subroot->point)){
        neighbor = subroot->point;
      }
      return neighbor;
    }

    if(smallerDimVal(query, subroot->point, dimension)){
      dimension = (dimension+1)%Dim;
      if(subroot->left != NULL){
        Point<Dim> p1 = findNearestNeighbor(query, subroot->left, neighbor, setup, dimension);
        if(shouldReplace(query, neighbor, p1)){
          neighbor = p1;
        }
        if(shouldReplace(query, neighbor, subroot->left->point)){
          neighbor = subroot->left->point;
        }
        int temp = pow((points[middle][dimension%Dim] - query[dimension%Dim]), 2)
        if(abs(subroot->left->point[dimension]-query[dimension]) < temp)){//calculateRadius(query, neighbor)){
          if(subroot->left->right != NULL){
            dimension = (dimension+1)%Dim;
            Point<Dim> p2 = findNearestNeighbor(query, subroot->left->right, neighbor, setup, dimension);
            if(shouldReplace(query, neighbor, p2)){
              neighbor = p2;
            }
          }
        }
      }
    }

    if(!smallerDimVal(query, subroot->point, dimension)){
      dimension = (dimension+1)%Dim;
      if(subroot->right != NULL){
        Point<Dim> p1 = findNearestNeighbor(query, subroot->right, neighbor, setup, dimension);
        if(shouldReplace(query, neighbor, p1)){
          neighbor = p1;
        }
        if(shouldReplace(query, neighbor, subroot->right->point)){
          neighbor = subroot->right->point;
        }
        int temp = pow((points[middle][dimension%Dim] - query[dimension%Dim]), 2);
        if(abs(subroot->right->point[dimension]-query[dimension]) < temp)){//calculateRadius(query, neighbor)){
          if(subroot->right->right != NULL){
            dimension = (dimension+1)%Dim;
            Point<Dim> p2 = findNearestNeighbor(query, subroot->right>left, neighbor, setup, dimension);
            if(shouldReplace(query, neighbor, p2)){
              neighbor = p2;
            }
          }
        }
      }
    }

    if(shouldReplace(query, neighbor, subroot->point)){
      neighbor = subroot->point;
    }
    return neighbor;*/
}

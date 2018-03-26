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
    //Helper
    KDTree(newPoints, 0, 0, newPoints.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints, int dimension, int left, int right){
    int middle = (left + right)/2;
    if(left < right){
      return;
    }

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
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

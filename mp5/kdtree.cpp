/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] < second[curDim]) return true;
    if (first[curDim]==second[curDim]) return first<second;
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sum = 0;
    for (int i = 0; i<Dim; i++){
      sum += pow((target[i]-currentBest[i]),2);
    }

    double sum1 = 0;
    for (int i = 0; i<Dim; i++){
      sum1 += pow((target[i]-potential[i]), 2);
    }

    if (sum1<sum) return true;
    if (sum1==sum) return potential<currentBest;
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    std::vector<Point<Dim>> v = newPoints;
    buildTree(v, root, 0);
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  clear(root);
  root = copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this!=rhs){
    clear(root);
    root = copy(rhs.root);
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
  return findNearestNeighbor(query, root, Point<Dim>(), false, 0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode* subroot, Point<Dim> candidate, bool setupLeaf, int splittingDim) const{
  //cout << "current: " << subroot->point << endl;

  if (subroot==NULL) return Point<Dim>();
  if (subroot->point==query) return query;
  if ((subroot->left==NULL && subroot->right==NULL) || (subroot->left==NULL && query[splittingDim]<subroot->point[splittingDim]) || (subroot->right==NULL && query[splittingDim]>subroot->point[splittingDim])){
    if (setupLeaf==false) candidate = subroot->point;
    if (shouldReplace(query, candidate, subroot->point)){
      candidate = subroot->point;
    }
    return candidate;
  }

  if (smallerDimVal(query, subroot->point, splittingDim)){
    if (subroot->left!=NULL){
      Point<Dim> p1 = findNearestNeighbor(query, subroot->left, candidate, setupLeaf, (splittingDim+1)%Dim);
      if (shouldReplace(query, candidate, p1)) candidate = p1;
      if (shouldReplace(query, candidate, subroot->point)) candidate = subroot->point;

      if (abs(subroot->point[splittingDim]-query[splittingDim])<calculateRadius(query, candidate)){
        if (subroot->right!=NULL){
          Point<Dim> p = findNearestNeighbor(query, subroot->right, candidate, setupLeaf, (splittingDim+1)%Dim);
          if (shouldReplace(query, candidate, p)) candidate = p;
        }
      }
    }
  }

  if (!smallerDimVal(query, subroot->point, splittingDim)){
    if (subroot->right!=NULL){
      Point<Dim> p1 = findNearestNeighbor(query, subroot->right, candidate, setupLeaf, (splittingDim+1)%Dim);
      if (shouldReplace(query, candidate, p1)) candidate = p1;
      if (shouldReplace(query, candidate, subroot->point)) candidate = subroot->point;

      if (abs(subroot->point[splittingDim]-query[splittingDim])<calculateRadius(query, candidate)){
        if (subroot->left!=NULL){
          Point<Dim> p = findNearestNeighbor(query, subroot->left, candidate, setupLeaf, (splittingDim+1)%Dim);
          if (shouldReplace(query, candidate, p)) candidate = p;
        }
      }
    }
  }
  if (shouldReplace(query, candidate, subroot->point)) candidate = subroot->point;
  return candidate;
}

template <int Dim>
double KDTree<Dim>::calculateRadius(Point<Dim> p1, const Point<Dim> p2) const{
  double radius = 0;
  for (int i = 0; i<Dim; i++){
    radius += pow(p1[i]-p2[i], 2);
  }
  radius = sqrt(radius);
  return radius;
}


template <int Dim>
size_t KDTree<Dim>::partition(vector<Point<Dim>>& v, int left, int right, int pivotIndex, int curDim){
  Point<Dim> pivotValue = v[pivotIndex];
  Point<Dim> temp = pivotValue;
  v[pivotIndex] = v[right];
  v[right] = temp;

  int storeIndex = left;
  for (int i = left; i<right; i++){
    if (v[i][curDim] < pivotValue[curDim]){
      Point<Dim> temp = v[i];
      v[i] = v[storeIndex];
      v[storeIndex] = temp;
      storeIndex++;
    }
  }
  Point<Dim> temp1 = v[right];
  v[right] = v[storeIndex];
  v[storeIndex] = temp1;

  return storeIndex;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findMedian(vector<Point<Dim>>& v, int left, int right, int curDim){

  if (left==right) return v[left];
  size_t pivotIndex = left+std::rand()%(right-left+1);
  pivotIndex = partition(v, left, right, pivotIndex, curDim);
  if (pivotIndex == (v.size()-1)/2) return v[pivotIndex];

  else if (pivotIndex < (v.size()-1)/2){
    return findMedian(v, pivotIndex+1, right, curDim);
  }
  else{
    return findMedian(v, left, pivotIndex-1, curDim);
  }
}


template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& v, KDTreeNode*& subroot, int curDim){
  if (!v.empty()){
    size_t s = v.size();
    subroot = new KDTreeNode(findMedian(v, 0, s-1, curDim));
    curDim = (curDim+1)%Dim;

    std::vector<Point<Dim>> v1;
    v1.assign(v.begin(), v.begin()+(s-1)/2);
    buildTree(v1, subroot->left, curDim);

    std::vector<Point<Dim>> v2;
    v2.assign(v.begin()+(s-1)/2+1, v.end());
    buildTree(v2, subroot->right, curDim);
  }
  else subroot = NULL;
}



template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot){
  if (subroot==NULL) return;
  clear(subroot->left);
  clear(subroot->right);
  delete subroot;
}

template <int Dim>
void KDTree<Dim>::clear(){
  if (root!=NULL) clear(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* subroot){
  if (subroot==NULL) return NULL;
  KDTreeNode* newNode = new KDTreeNode(subroot->point);
  newNode->left = copy(subroot->left);
  newNode->right = copy(subroot->right);
  return newNode;
}

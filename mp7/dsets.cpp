/* Your code here! */
#include <vector>
#include "dsets.h"

void DisjointSets::addelements(int num){
  for(int i=0; i<num; i++){
    vec.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(vec[elem] <0){
    return elem;
  }
  else{
    return vec[elem] = find(vec[elem]);
  }
}

void DisjointSets::setunion(int a, int b){
  int x = find(a);
  int y = find(b);
  int union1 = size(x)+size(y);
  if(x>y){
    vec[x]=y;
    vec[y]=union1;
  }
  else{
    vec[y]=x;
    vec[x]=union1;
  }
}

int DisjointSets::size(int elem){
  return vec[elem];
}

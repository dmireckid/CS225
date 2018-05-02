#include "maze.h"
#include <queue>
#include <map>
#include <vector>

SquareMaze::SquareMaze(){
  width_ = 0;
  height_ = 0;
  size_ = 0;
}

void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  size_ = width*height;
  maze_.addelements(size_);
  for(int i=0; i<size_; i++){
    downWall.push_back(true);
    rightWall.push_back(true);
  }
  int n=0;
  bool dir;
  while(n < size_/2){
    int randomRow = rand()%(height_-1);
    int randomCol = rand()%(width_-1);
    int regular = randomRow*width_ + randomCol;
    int right = randomRow*width_ + randomCol +1;
    int down = (randomRow+1)*width_ + randomCol;
    dir = rand()%10 > 4;
    if(dir){
      if(rightWall[regular] && maze_.find(regular) != maze_.find(right)){
        rightWall[regular] = false;
        maze_.setunion(regular, right);
        n++;
        dir = false;
      }
    }
    else{
      if(downWall[regular] && maze_.find(regular) != maze_.find(down)){
        downWall[regular] = false;
        maze_.setunion(regular, down);
        n++;
        dir = true;
      }
    }
  }
  int i;
  for(i=0; i<height_-1; i++){
    int j;
    for(j=0; j<width_-1; j++){
      int regular2 = i*width_ + j;
      int right2 = i*width_ + j +1;
      int down2 = (i+1)*width_ + j;
      if(dir){
        dir=false;
        if(rightWall[regular2] && maze_.find(regular2) != maze_.find(right2)){
          rightWall[regular2] = false;
          maze_.setunion(regular2, right2);
        }
        if(downWall[regular2] && maze_.find(regular2) != maze_.find(down2)){
          downWall[regular2] = false;
          maze_.setunion(regular2, down2);
        }
      }
      else{
        dir=true;
        if(downWall[regular2] && maze_.find(regular2) != maze_.find(down2)){
          downWall[regular2] = false;
          maze_.setunion(regular2, down2);
        }
        if(rightWall[regular2] && maze_.find(regular2) != maze_.find(right2)){
          rightWall[regular2] = false;
          maze_.setunion(regular2, right2);
        }
      }
    }
      //edge cases
    //std::cout << i << j << std::endl;
    int regular2 = i*width_ + j;
    //int ight2 = i*width_ + j +1;
    int down2 = (i+1)*width_ + j;
    if(downWall[regular2] && maze_.find(regular2) != maze_.find(down2)){
        downWall[regular2] = false;
        maze_.setunion(regular2, down2);
    }
  }
  for(int j=0; j<width_-1; j++){
      int regular2 = i*width_ + j;
      int right2 = i*width_ + j +1;
      int down2 = (i+1)*width_ + j;
      if(rightWall[regular2] && maze_.find(regular2) != maze_.find(right2)){
        rightWall[regular2] = false;
        maze_.setunion(regular2, right2);
      }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  if(dir==0 && x+1 < width_){
    if(rightWall[width_*y +x] == false){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir==1 && y+1 < height_){
    if(downWall[width_*y +x] == false){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir==2 && x > 0){
    if(rightWall[width_*y +x -1] == false){
      return true;
    }
    else{
      return false;
    }
  }
  if(dir==3 && y > 0){
    if(downWall[width_*(y-1) +x] == false){
      return true;
    }
    else{
      return false;
    }
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int loc = width_*y + x;
  if(x>=0 && x<width_ && y>=0 && y<height_){
    if(dir==0){
      rightWall[loc] = exists;
    }
    if(dir==1){
      downWall[loc] = exists;
    }
  }
  else{
    return;
  }
}

std::vector<int> SquareMaze::solveMaze(){
  //TODO
  map<int,int> parent;
  queue<int> que;
  vector<int> solution;
  int entrance = 0;
  que.push(entrance);
  parent[entrance] = -1;
  while(!que.empty()){
    int temp = que.front();
    que.pop();
    for(int i=0; i<4; i++){
      int x = temp%width_;
      int y = temp/width_;
      if(i==0){
        x++;
      }
      else if(i==1){
        y++;
      }
      else if(i==2){
        x--;
      }
      else if(i==3){
        y--;
      }
      int loc = y*width_ + x;
      if(canTravel(temp%width_, temp/width_, i) && parent[temp]!=loc){
        parent[loc] = temp;
        que.push(loc);
      }
    }
  }
  for(int i=0; i<width_; i++){
    int finish = (height_-1)*width_ + i;
    vector<int> possible;
    while(entrance != finish){
      int temp2 = parent[finish];
      if(finish-temp2 == 1){
        possible.push_back(0);

      }
      else if(finish-temp2 == -1){
        possible.push_back(2);
      }
      else if(finish-temp2 == width_){
        possible.push_back(1);
      }
      else if(finish-temp2 == -(width_)){
        possible.push_back(3);
      }
      finish = temp2;
    }
    if(possible.size() > solution.size()){
      solution = possible;
    }
  }
  std::reverse(solution.begin(), solution.end());
  return solution;
}

cs225::PNG* SquareMaze::drawMaze() const{
  cs225::PNG* maze = new cs225::PNG(width_*10 +1, height_*10 +1);
  for(unsigned int x=10; x<maze->width(); x++){
    cs225::HSLAPixel& pix = maze->getPixel(x,0);
    pix.h=0;
    pix.s=0;
    pix.l=0;
    pix.a=1;
  }
  for(unsigned int y=0; y<maze->height(); y++){
    cs225::HSLAPixel& pix = maze->getPixel(0,y);
    pix.h=0;
    pix.s=0;
    pix.l=0;
    pix.a=1;
  }
  for(int i=0; i<width_; i++){
    for(int j=0; j<height_; j++){
      int loc = width_*j + i;
      if(rightWall[loc]){
        for(int k=0; k<=10; k++){
          cs225::HSLAPixel& pix = maze->getPixel((i+1)*10, j*10+k);
          pix.h=0;
          pix.s=0;
          pix.l=0;
          pix.a=1;
        }
      }
      if(downWall[loc]){
        for(int k=0; k<=10; k++){
          cs225::HSLAPixel& pix = maze->getPixel(i*10+k, (j+1)*10);
          pix.h=0;
          pix.s=0;
          pix.l=0;
          pix.a=1;
        }
      }
    }
  }
  return maze;
}

cs225::PNG* SquareMaze::drawMazeWithSolution(){
  cs225::PNG* solvedMaze = drawMaze();
  vector<int> solution = solveMaze();
  int y=5, x=5;
  //int x=5;
  for(int i=0; i<(int)solution.size(); i++){
    if(solution[i]==0){
      for(int j=0; j<=10; j++){
        cs225::HSLAPixel& pix = solvedMaze->getPixel(x+j, y);
        pix.h=0;
        pix.s=1;
        pix.l=0.5;
        pix.a=1;
      }
      x=x+10;
    }
    else if(solution[i]==1){
      for(int j=0; j<=10; j++){
        cs225::HSLAPixel& pix = solvedMaze->getPixel(x, y+j);
        pix.h=0;
        pix.s=1;
        pix.l=0.5;
        pix.a=1;
      }
      y=y+10;
    }
    else if(solution[i]==2){
      for(int j=0; j<=10; j++){
        cs225::HSLAPixel& pix = solvedMaze->getPixel(x-j, y);
        pix.h=0;
        pix.s=1;
        pix.l=0.5;
        pix.a=1;
      }
      x=x-10;
    }
    else{//} if(solution[i]==3){
      for(int j=0; j<=10; j++){
        cs225::HSLAPixel& pix = solvedMaze->getPixel(x, y-j);
        pix.h=0;
        pix.s=1;
        pix.l=0.5;
        pix.a=1;
      }
      y=y-10;
    }
  }
  x = x/10;
  y = height_-1;
  for(int z=1; z<=9; z++){
    cs225::HSLAPixel& pix = solvedMaze->getPixel(x*10 + z, (y+1)*10);
    pix.h=0;
    pix.s=0;
    pix.l=1;
    pix.a=1;
  }
  return solvedMaze;
}

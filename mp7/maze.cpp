#include "maze.h"

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
  int i, j, regular2, right2, down2;
  for(i=0; i<height_-1; i++){
    for(j=0; j<width_-1; j++){
      regular2 = i*width_ + j;
      right2 = i*width_ + j +1;
      down2 = (i+1)*width_ + j;
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
    if(downWall[regular2] && maze_.find(regular2) != maze_.find(down2)){
        downWall[regular2] = false;
        maze_.setunion(regular2, down2);
    }
  }
  for(j=0; j<width_-1; j++){
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
  return true;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  return;
}

std::vector<int> SquareMaze::solveMaze(){
  std::vector<int> v;
  return v;
}

cs225::PNG* SquareMaze::drawMaze() const{
  cs225::PNG* result = NULL;
  return result;
}

cs225::PNG* SquareMaze::drawMazeWithSolution(){
  cs225::PNG* result = NULL;
  return result;
}

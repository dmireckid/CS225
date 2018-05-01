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
  std::vector<int> v;
  return v;
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
  cs225::PNG* result = NULL;
  return result;
}

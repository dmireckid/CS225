
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  PNG myPNG;
  myPNG.readFromFile("myPNG.png");
  FloodFilledImage image(myPNG);
  DFS dfs(myPNG, Point(100, 50), 0.5);
  //HSLAPixel color(100, 1, 0.5);
  MyColorPicker my(.05);
  image.addFloodFill( dfs, my );

  BFS bfs(myPNG, Point(50, 100), 0.5);
  //HSLAPixel color2(200, 1, 0.5);
  MyColorPicker my2(.02);
  image.addFloodFill( bfs, my2 );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  return 0;
}

#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  png_ = png;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */

  blah2.push_back(&traversal);
  colour.push_back(&colorPicker);

}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  /*PNG* og = new PNG(png_);
  PNG* supreme = NULL;
  unsigned frameIntMe = 0;


  new png png_
  add frames
  temp new current
  iterate addFloodFill vector
  fps++ % frameInterval/ add new frame each frameInterval
  make copies of png temp=newcurr*/
  animation.addFrame(png_);
  int framee = 0;
  for(unsigned long i=0; i < blah2.size(); i++){
    ImageTraversal* it = blah2[i];
    ColorPicker* cp = colour[i];
    for(ImageTraversal::Iterator iter = it->begin(); iter != it->end(); ++iter){
      HSLAPixel& pix = png_.getPixel(iter.current_.x, iter.current_.y);
      pix = cp->getColor(iter.current_.x, iter.current_.y);
      framee++;
      if(framee%frameInterval == 0){
        animation.addFrame(png_);
        framee = 1;
      }
    }
  }
  animation.addFrame(png_);
  return animation;
}

#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image picture, sticker, sticker2, sticker3, myPic;
  picture.readFromFile("Base.png");
  sticker.readFromFile("sticker.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");
  StickerSheet sheet(picture, 3);
  sheet.addSticker(sticker, 50, 50);
  sheet.addSticker(sticker2, 40, 40);
  sheet.addSticker(sticker3, 60, 60);
  myPic=sheet.render();
  myPic.writeToFile("myImage.png");
  return 0;
}

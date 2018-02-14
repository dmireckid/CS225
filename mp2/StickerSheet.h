/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"



class StickerSheet{
public:
  StickerSheet(const Image &picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet & operator= (const StickerSheet &other);
  void changeMaxStickers(unsigned max);
  int addSticker(Image &sticker, unsigned x, unsigned y);
  bool translate(unsigned index, unsigned x, unsigned y);
  void removeSticker(unsigned index);
  Image* getSticker(unsigned index) const;
  Image render() const;
  void clear();
  void copy(const StickerSheet & copee);
private:
  Image** imArr_;
  int *StickerX, *StickerY;
  unsigned int max_;
  Image* picture_;
};

#endif

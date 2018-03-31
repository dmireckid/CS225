/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    double hsl[3], hsl2[3];
    vector<Point<3>> pixels;
    map<Point<3>, int> mapp;

    for(size_t i=0; i<theTiles.size(); i++){
      HSLAPixel p1 = theTiles[i].getAverageColor();
      hsl[0] = p1.h/360;
      hsl[1] = p1.s;
      hsl[2] = p1.l;

      Point<3> p2(hsl);
      pixels.push_back(p2);
    }

    for(size_t i=0; i<pixels.size(); i++){
      mapp[pixels[i]] = i;
    }

    KDTree<3>::KDTree tree(pixels);
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* result = new MosaicCanvas(rows, cols);

    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        HSLAPixel general = theSource.getRegionColor(i, j);
        hsl2[0] = general.h/360;
        hsl2[1] = general.s;
        hsl2[2] = general.l;

        Point<3> g(hsl2);
        Point<3> finale = tree.findNearestNeighbor(g);
        int index = mapp[finale];
        TileImage* tile = new TileImage(theTiles[index]);
        result->setTile(i,j,tile);
      }
    }

    return result;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}

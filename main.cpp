#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

vector<Mat> getRegions(const int RADIUS, const Mat &src, int x, int y);

int main(void) {
  const string IMG_PATH = "./res/",
               IMG_NAME = "me",
               IMG_EXT  = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  Mat inputImg = imread(IMG_FILENAME, IMREAD_GRAYSCALE);

  // Algorithm parameters
  // RADIUS (a) = kernel radius
  const int RADIUS = 10;
  int x = 201, y = 201;

  vector<Mat> regions = getRegions(RADIUS, inputImg, x, y);

  waitKey();
  return 0;
}

vector<Mat> getRegions(const int RADIUS, const Mat &src, int x, int y) {
  if(
    ((x - RADIUS) < 0) ||
    ((y - RADIUS) < 0) ||
    ((x + RADIUS) > src.cols) ||
    ((y + RADIUS) > src.rows)
  ) exit(EXIT_FAILURE);

  vector<Mat> regions{4};

  regions[0] = src(Rect(Point(x - RADIUS, y - RADIUS), Point(         x,          y)));
  regions[1] = src(Rect(Point(         x, y - RADIUS), Point(x + RADIUS,          y)));
  regions[2] = src(Rect(Point(x - RADIUS, y + RADIUS), Point(         x,          y)));
  regions[3] = src(Rect(Point(         x,          y), Point(x + RADIUS, y + RADIUS)));

  return regions;
}

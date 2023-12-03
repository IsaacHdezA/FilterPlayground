#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

struct Region {
  Mat pixels;

  double mean;
  double stdDev;

  void print() const {
    cout << pixels             << '\n'
         << "Mean: "           << mean   << '\n'
         << "Std. Deviation: " << stdDev << '\n' << endl;
  }
};

vector<Region> getRegions(const int RADIUS, const Mat &src, int x, int y);
uchar getKuwaharaPixel(const vector<Region> &regions);

int main(void) {
  const string IMG_PATH = "./res/",
               IMG_NAME = "suncat",
               IMG_EXT  = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  Mat inputImg = imread(IMG_FILENAME, IMREAD_GRAYSCALE),
      outputImg = Mat::zeros(inputImg.rows, inputImg.cols, CV_8UC1);

  // Algorithm parameters
  // RADIUS (a) = kernel radius
  const int RADIUS = 5;

  vector<Region> regions{4};

  // Iterate every pixel
  for(int r = RADIUS; r < inputImg.rows - RADIUS; r++) {
    uchar  *inputRow = (uchar *)  inputImg.ptr<uchar>(r),
          *outputRow = (uchar *) outputImg.ptr<uchar>(r);

    for(int c = RADIUS; c < inputImg.cols - RADIUS; c++) {
      regions = getRegions(RADIUS, inputImg, c, r);
      outputRow[c] = getKuwaharaPixel(regions);
    }
  }

  imwrite("./output/" + IMG_NAME + "_r" + to_string(RADIUS) + IMG_EXT, outputImg);

  waitKey();
  return 0;
}

vector<Region> getRegions(const int RADIUS, const Mat &src, int x, int y) {
  if(
    ((x - RADIUS) < 0) ||
    ((y - RADIUS) < 0) ||
    ((x + RADIUS) > src.cols) ||
    ((y + RADIUS) > src.rows)
  ) {
    cout << "Pixel indices out of bounds (" << x << ", " << y << ")" << endl;
    exit(EXIT_FAILURE);
  }

  vector<Region> regions{4};

  regions[0].pixels = src(Rect(Point(x - RADIUS, y - RADIUS), Point(         x,          y)));
  regions[1].pixels = src(Rect(Point(         x, y - RADIUS), Point(x + RADIUS,          y)));
  regions[2].pixels = src(Rect(Point(x - RADIUS, y + RADIUS), Point(         x,          y)));
  regions[3].pixels = src(Rect(Point(         x,          y), Point(x + RADIUS, y + RADIUS)));

  Scalar mean, stdDev;
  for(Region &region : regions) {
    meanStdDev(region.pixels, mean, stdDev);
    region.mean = mean[0];
    region.stdDev = stdDev[0];
  }

  return regions;
}

uchar getKuwaharaPixel(const vector<Region> &regions) {
  double min = 0;

  for(int i = 0; i < regions.size(); i++) {
    if(regions[i].stdDev < regions[min].stdDev) min = i;
  }

  return (uchar) regions[min].mean;
}
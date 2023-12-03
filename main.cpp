#include "kuwahara.hpp"
#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

inline float map(float val, float start1, float stop1, float start2, float stop2) {
  return (((stop2 - start2) / (stop1 - start1)) * val + start2);
}

Mat getGrayscale(int width, int height);

class Dither {
  public:
    Dither();

    static Mat applyFilter(const Mat &src);

  private:
    static const Mat THRESH_MAP_4;
    static const Mat THRESH_MAP_16;
};

const Mat Dither::THRESH_MAP_4 = (Mat_<float>(2, 2) <<
    0.0/4, 2.0/4,
    3.0/4, 1.0/4
 );

const Mat Dither::THRESH_MAP_16 = (Mat_<float>(4, 4) <<
   0.0/16,  8.0/16,  2.0/16, 10.0/16,
  12.0/16,  4.0/16, 14.0/16,  6.0/16,
   3.0/16, 11.0/16,  1.0/16,  9.0/16,
  15.0/16,  7.0/16, 13.0/16,  5.0/16
);

Mat Dither::applyFilter(const Mat &src) {
  Mat output = src.clone();
  cvtColor(output, output, COLOR_BGR2GRAY);

  for(int i = 0; i < output.rows; i++) {
    int mapRowId = i % THRESH_MAP_16.rows;

    float    *mapRow = (float *) THRESH_MAP_16.ptr<float>(mapRowId);
    uchar *outputRow = (uchar *) output.ptr<uchar>(i);

    for(int j = 0; j < output.cols; j++) {
      int mapCol = j % THRESH_MAP_16.cols;
      outputRow[j] = (outputRow[j]/255.0 > mapRow[mapCol]) ? 255 : 0;
    }
  }

  return output;
}

int main(int argc, char *argv[]) {
  const string IMG_PATH = "../../res/",
               IMG_NAME = "me",
               IMG_EXT = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  cout << "File: " << IMG_FILENAME << endl;
  Mat inputImg  = imread(IMG_FILENAME, IMREAD_COLOR),
      outputImg = Dither::applyFilter(inputImg);

  cout << "Test" << endl;
  imshow("Output", outputImg);
  waitKey();
  return 0;
}

Mat getGrayscale(int width, int height) {
  Mat output = Mat::zeros(width, height, CV_8UC1);
  
  // Creating grayscale image
  for(int r = 0; r < output.rows; r++) {
    uchar *outputRows = (uchar *) output.ptr<uchar>(r);

    for(int c = 0; c < output.cols; c++)
      outputRows[c] = map(c, 0, output.cols, 0, 255);
  }

  return output;
}

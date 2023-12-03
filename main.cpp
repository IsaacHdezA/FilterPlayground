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

int main(int argc, char *argv[]) {
  const string IMG_PATH = "../../res/",
               IMG_NAME = "suncat",
               IMG_EXT = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  cout << "File: " << IMG_FILENAME << endl;
  Mat inputImg  = imread(IMG_FILENAME, IMREAD_COLOR),
      outputImg = getGrayscale(512, 512);

  const Mat THRESH_MAP_4 = (Mat_<int>(2, 2) <<
    0, 2,
    3, 1
  );

  const Mat THRESH_MAP_16 = (Mat_<int>(4, 4) <<
     0,  8,  2, 10,
    12,  4, 14,  6,
     3, 11,  1,  9,
    15,  7, 13,  5
  );

  cout << "Threshold map 4:  " << THRESH_MAP_4  << '\n'
       << "Threshold map 16: " << THRESH_MAP_16 << '\n' << endl;

  imshow("Output", outputImg);
  waitKey();
  return 0;
}

Mat getGrayscale(int width, int height) {
  Mat output = Mat::zeros(512, 512, CV_8UC1);
  
  // Creating grayscale image
  for(int r = 0; r < output.rows; r++) {
    uchar *outputRows = (uchar *) output.ptr<uchar>(r);

    for(int c = 0; c < output.cols; c++)
      outputRows[c] = map(c, 0, output.cols, 0, 255);
  }

  return output;
}

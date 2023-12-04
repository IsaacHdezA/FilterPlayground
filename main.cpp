#include <iostream>

using namespace std;

#include "kuwahara.hpp"
#include "dither.hpp"

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
               IMG_NAME = "catguitar",
               IMG_EXT = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  cout << "File: " << IMG_FILENAME << endl;
  Mat inputImg  = imread(IMG_FILENAME, IMREAD_COLOR),
      // outputImg = Kuwahara::applyFilter(inputImg, 12);
      // outputImg = Dither::applyFilter(inputImg);
      outputImg = Dither::applyFilter(Kuwahara::applyFilter(inputImg, 12));
  

  const string OUTPUT_PATH = "../../output/" + IMG_NAME + "_dithered.jpg";

  imwrite(OUTPUT_PATH, outputImg);
  cout << "Image written into: " << OUTPUT_PATH << endl;

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

#include "kuwahara.hpp"
#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(void) {
  const string IMG_PATH = "./res/",
               IMG_NAME = "idaho",
               IMG_EXT  = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  const int RADIUS = 5;

  Mat inputImg = imread(IMG_FILENAME, IMREAD_GRAYSCALE),
      outputImg = Kuwahara::applyFilter(inputImg, RADIUS);

  imwrite("./output/" + IMG_NAME + "_r" + to_string(RADIUS) + IMG_EXT, outputImg);

  waitKey();
  return 0;
}
#include "kuwahara.hpp"
#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, char *argv[]) {
  // if(argc < 2 || argc > 4) {
  //   cerr << "Incorrect usage. Usage is..." << endl;
  //   cerr << "\tkuwuhara <inputImg> <radius> <outputImg>" << endl;

  //   exit(EXIT_FAILURE);
  // }

  // const string OUTPUT_PATH = "../../output/r" + to_string(atoi(argv[2])) + "_" + string(argv[3]);

  // cout << "Input image path: " << argv[1] << '\n'
  //      << "Kernel radius:    " << argv[2] << '\n'
  //      << "Output image:     " << OUTPUT_PATH << '\n' << endl;

  // Mat inputImg = imread(argv[1], CV_8UC1),
  //     outputImg = Kuwahara::applyFilter(inputImg, atoi(argv[2]));

  // imwrite(OUTPUT_PATH, outputImg);

  const int RADIUS = 10;

  const string IMG_PATH = "./res/",
               IMG_NAME = "mano",
               IMG_EXT = ".jpg",
               IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

  cout << IMG_FILENAME << endl;
  Mat inputImg = imread(IMG_FILENAME, IMREAD_COLOR),
      outputImg;

  cvtColor(inputImg, outputImg, COLOR_BGR2HSV);

  vector<Mat> channels{3};
  split(outputImg, channels);
  channels[2] = Kuwahara::applyFilter(channels[2], RADIUS);
  merge(channels, outputImg);
  cvtColor(outputImg, outputImg, COLOR_HSV2BGR);

  imwrite("./output/" + IMG_NAME + "_r" + to_string(RADIUS) + ".jpg", outputImg);

  waitKey();
  return 0;
}

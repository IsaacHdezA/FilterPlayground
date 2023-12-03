#include "kuwahara.hpp"
#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, char *argv[]) {
  if(argc < 2 || argc > 4) {
    cerr << "Incorrect usage. Usage is..." << endl;
    cerr << "\tkuwuhara <inputImg> <radius> <outputImg>" << endl;

    exit(EXIT_FAILURE);
  }

  const string OUTPUT_PATH = "../../output/r" + to_string(atoi(argv[2])) + "_" + string(argv[3]);

  cout << "Input image path: " << argv[1]     << '\n'
       << "Kernel radius:    " << argv[2]     << '\n'
       << "Output image:     " << OUTPUT_PATH << '\n' << endl;

  Mat inputImg = imread(argv[1], CV_8UC1),
      outputImg = Kuwahara::applyFilter(inputImg, atoi(argv[2]));

  imwrite(OUTPUT_PATH, outputImg);

  waitKey();
  return 0;
}

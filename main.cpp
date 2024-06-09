#include <iostream>
#include <string>
#include <vector>

using namespace std;
using std::string;

#include "include/kmeans.hpp"
#include "include/kuwahara.hpp"
#include "include/dither.hpp"

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

inline float map(float val, float start1, float stop1, float start2, float stop2) {
  return (((stop2 - start2) / (stop1 - start1)) * val + start2);
}

Mat getGrayscale(int width, int height);
size_t findLastChar(char c, string str);
vector<string> tokenizePath(string path);

int main(int argc, char *argv[]) {
  if(argc > 1) {
    string filepath = argv[1];

    vector<string> pathParts = tokenizePath(filepath);
    const string IMG_PATH      = pathParts[0],
                 IMG_NAME      = pathParts[1],
                 IMG_EXT       = pathParts[2],
                 IMG_FILENAME  = IMG_PATH + IMG_NAME + IMG_EXT;

    cout << "File: " << IMG_FILENAME << endl;
    Mat inputImg     = imread(IMG_FILENAME, IMREAD_COLOR),
        // outputImg = Kuwahara::applyFilter(inputImg, 12);
        // outputImg = Dither::applyFilter(inputImg);
        // outputImg = Dither::applyFilter(Kuwahara::applyFilter(inputImg, 12));
        outputImg = KMeans::applyFilter(inputImg, 5);

    const string OUTPUT_PATH = IMG_PATH + IMG_NAME + "_dithered.jpg";

    imwrite(OUTPUT_PATH, outputImg);
    cout << "Image written into: " << OUTPUT_PATH << endl;

    return 0;
  }

  cout << "Wrong usage. You have to specify the image's path" << endl;

  return 1;
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

size_t findLastChar(char c, string str) {
  size_t dir = 0;

  while(dir != string::npos) {
    int temp = str.find(c, dir + 1);
    if(temp == string::npos) break;

    dir = temp;
  }

  return dir;
}

vector<string> tokenizePath(string path) {
  vector<string> sections{3};
  int path_pos = findLastChar('/', path), ext_pos = findLastChar('.', path);

  sections[0] = path.substr(0, path_pos + 1);
  sections[1] = path.substr(path_pos + 1, ext_pos - (path_pos + 1));
  sections[2] = path.substr(ext_pos);

  return sections;
}

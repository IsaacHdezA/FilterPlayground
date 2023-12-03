#include <iostream>

using namespace std;

// OpenCV libraries and namespaces
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(void) {
    const string IMG_PATH = "./res/",
                 IMG_NAME = "me",
                 IMG_EXT  = ".jpg",
                 IMG_FILENAME = IMG_PATH + IMG_NAME + IMG_EXT;

    cout << "Input image path: " << IMG_FILENAME << endl;
    Mat output = imread(IMG_FILENAME);
    imshow("hola", output);

    waitKey();
    return 0;
}

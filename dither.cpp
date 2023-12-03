#include "./dither.hpp"

#include <opencv2/imgproc/imgproc.hpp>

const cv::Mat Dither::THRESH_MAP_4 = (cv::Mat_<float>(2, 2) <<
    0.0/4, 2.0/4,
    3.0/4, 1.0/4
 );

const cv::Mat Dither::THRESH_MAP_16 = (cv::Mat_<float>(4, 4) <<
   0.0/16,  8.0/16,  2.0/16, 10.0/16,
  12.0/16,  4.0/16, 14.0/16,  6.0/16,
   3.0/16, 11.0/16,  1.0/16,  9.0/16,
  15.0/16,  7.0/16, 13.0/16,  5.0/16
);

cv::Mat Dither::applyFilter(const cv::Mat &src) {
	Dither proxy;
	
	if(src.channels() > 1) {
		cv::Mat output;
		cvtColor(src, output, cv::COLOR_BGR2HSV);

		std::vector<cv::Mat> channels{3};
		cv::split(output, channels);

		channels[2] = proxy.applyFilter(channels[2]);

		merge(channels, output);
		cv::cvtColor(output, output, cv::COLOR_HSV2BGR);

		return output;
	}

  return proxy.applyToChannel(src);
}

cv::Mat Dither::applyToChannel(const cv::Mat &src) {
	cv::Mat output = src.clone();

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
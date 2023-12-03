#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "kuwahara.hpp"

cv::Mat Kuwahara::applyFilter(const cv::Mat &src, int RADIUS) {
  Kuwahara proxy;

  if(src.channels() > 1) {
    cv::Mat output;
    cvtColor(src, output, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> channels{3};
    cv::split(output, channels);

    channels[2] = proxy.applyToChannel(channels[2], RADIUS);

    merge(channels, output);
    cv::cvtColor(output, output, cv::COLOR_HSV2BGR);

    return output;
  }

  cv::Mat output = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
  output = proxy.applyToChannel(src, RADIUS);

  return output;
}

cv::Mat Kuwahara::applyToChannel(const cv::Mat &src, int RADIUS) {
  Kuwahara proxy;
  cv::Mat output = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);

  std::vector<Region> regions{4};

  // Iterate every pixel
  for(int r = RADIUS; r < src.rows - RADIUS; r++) {
    uchar *outputRow = (uchar *) output.ptr<uchar>(r);

    for(int c = RADIUS; c < src.cols - RADIUS; c++) {
      regions = proxy.getRegions(RADIUS, src, c, r);
      outputRow[c] = proxy.getKuwaharaPixel(regions);
    }
  }

  return output;
}

std::vector<Region> Kuwahara::getRegions(const int RADIUS, const cv::Mat &src, int x, int y) {
  if(
    ((x - RADIUS) < 0) ||
    ((y - RADIUS) < 0) ||
    ((x + RADIUS) > src.cols) ||
    ((y + RADIUS) > src.rows)
  ) {
    std::cout << "Pixel indices out of bounds (" << x << ", " << y << ")" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<Region> regions{4};

  regions[0].pixels = src(cv::Rect(cv::Point(x - RADIUS, y - RADIUS), cv::Point(         x,          y)));
  regions[1].pixels = src(cv::Rect(cv::Point(         x, y - RADIUS), cv::Point(x + RADIUS,          y)));
  regions[2].pixels = src(cv::Rect(cv::Point(x - RADIUS, y + RADIUS), cv::Point(         x,          y)));
  regions[3].pixels = src(cv::Rect(cv::Point(         x,          y), cv::Point(x + RADIUS, y + RADIUS)));

  cv::Scalar mean, stdDev;
  for(Region &region : regions) {
    meanStdDev(region.pixels, mean, stdDev);
    region.mean = mean[0];
    region.stdDev = stdDev[0];
  }

  return regions;
}

uchar Kuwahara::getKuwaharaPixel(const std::vector<Region> &regions) {
  double min = 0;

  for(int i = 0; i < (int) regions.size(); i++) {
    if(regions[i].stdDev < regions[min].stdDev) min = i;
  }

  return (uchar) regions[min].mean;
}


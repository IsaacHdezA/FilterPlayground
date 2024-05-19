#pragma once

#include "opencv2/core/core.hpp"
#include <vector>

struct Region {
  cv::Mat pixels;

  double mean;
  double stdDev;
};

class Kuwahara {
  public:
    static cv::Mat applyFilter(const cv::Mat &src, int RADIUS = 3);

  private:
    std::vector<Region> getRegions(const int RADIUS, const cv::Mat &src, int x, int y);
    cv::Mat applyToChannel(const cv::Mat &src, int RADIUS);
    uchar getKuwaharaPixel(const std::vector<Region> &regions);
};
#pragma once

#include <opencv2/core/core.hpp>

class Dither {
  public:
    static cv::Mat applyFilter(const cv::Mat &src);

  private:
    static const cv::Mat THRESH_MAP_4;
    static const cv::Mat THRESH_MAP_16;

		cv::Mat applyToChannel(const cv::Mat &src);
};
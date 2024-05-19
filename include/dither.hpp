#pragma once

#include <opencv2/core/core.hpp>

class Dither {
  public:
    Dither(int n = 4);
    Dither(cv::Mat THRESH_MAP);

    static cv::Mat applyFilter(const cv::Mat &src, int n = 4);
    cv::Mat getThreshMap() const;
    void setThreshMap(const cv::Mat THRESH_MAP);
    void setThreshMap(int n);
    cv::Mat createThreshMap(int n);

  private:
    cv::Mat THRESH_MAP;

		cv::Mat applyToChannel(const cv::Mat &src);
};
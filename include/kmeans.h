#pragma once

#include <cmath>
#include <opencv2/core/core.hpp>

class KMeans {
  public:
    static cv::Mat applyFilter(const cv::Mat &src, int k = 4);

  private:
    int k;
    int iter;
    std::vector<cv::Mat> centroids;
    cv::Mat src;

    cv::Mat kMeans(int k, int iter = 500);

    int randInt(int min, int max = 0) { return (rand() % (max - min)) + min; } 
    int minIdx();
    void findClosestCentroids();
    void computeCentroids();
}

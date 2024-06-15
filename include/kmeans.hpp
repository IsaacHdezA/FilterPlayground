#pragma once

#include <cmath>
#include <opencv2/core/core.hpp>

class KMeans {
  public:
    static cv::Mat applyFilter(const cv::Mat &src, int k = 4);

  private:
    int randInt(int min, int max = 0) { return (rand() % (max - min)) + min; } 

    cv::Mat kMeans(const cv::Mat &src, int k, int iter = 500);

    uchar minIdx(const cv::Mat distances);
    void initializeCentroids(const cv::Mat &src, cv::Mat centroids, int k);
    void findClosestCentroids(const cv::Mat &src, const cv::Mat &centroids, cv::Mat &memberships);
    void computeCentroids(const cv::Mat &src, cv::Mat &centroids, const cv::Mat &memberships);

    template<typename T>
    float distance(const T &pt1, const T &pt2);
};

#pragma once

#include <cmath>
#include <opencv2/core/core.hpp>

class KMeans {
  public:
    static cv::Mat applyFilter(const cv::Mat &src, int k = 4, int iter = 100);

  private:
    int randInt(int min, int max = 0) { return (rand() % (max - min)) + min; } 

    cv::Mat kMeans(const cv::Mat &src, int k, int iter = 500);

    uchar minIdx(const std::vector<float> distances);
    void initializeCentroids(const cv::Mat &src, std::vector<cv::Vec3b> &centroids, int k);
    void findClosestCentroids(const cv::Mat &src, const std::vector<cv::Vec3b> &centroids, std::vector<uchar> &memberships);
    void computeCentroids(const cv::Mat &src, std::vector<cv::Vec3b> &centroids, const std::vector<uchar> &memberships);

    template<typename T>
    float distance(const T &pt1, const T &pt2);
    cv::Mat buildImage(const cv::Mat &src, const std::vector<cv::Vec3b> &centroids, const std::vector<uchar> &memberships);
};

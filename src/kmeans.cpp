#include <iostream>

using namespace std;

#include "../include/kmeans.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// KMeans::KMeans(const cv::Mat &src, int k) {
//   this->src = src.clone();
//   this->centroids = cv::Mat::zeros(k, 1, this->src.type());
// }  

cv::Mat KMeans::applyFilter(const cv::Mat &src, int k) {
  KMeans proxy;

  cv::Mat output = proxy.kMeans(src, k, 200) ;
  cv::Mat resizedOutput;

  cv::resize(output, resizedOutput, cv::Size(500, 500), 0, 0, cv::INTER_LINEAR);

  imshow("Source image", resizedOutput);
  cv::waitKey();

  return output;
}

cv::Mat KMeans::kMeans(const cv::Mat &src, int k, int iter) {
  KMeans proxy;
  cv::Mat output = src.clone();
  cv::Mat centroids = cv::Mat::zeros(k, 1, src.type());

  // 1. Initialize Centroids
  proxy.initializeCentroids(src, centroids, k);

  // 2. Repeat:
  for(int i = 0; i < iter; i++) {
    // 1. Assign points to cluster centroids
    // 2. Move cluster centroids
  }

  return output; 
}

void KMeans::initializeCentroids(const cv::Mat &src, cv::Mat centroids, int k) {
  KMeans proxy;

  for(int i = 0; i < k; i++) {
    int randY = proxy.randInt(0, src.rows),
        randX = proxy.randInt(0, src.cols);
    
    centroids.at<cv::Vec3b>(i) = src.at<cv::Vec3b>(randY, randX);
  }
}

int KMeans::minIdx() {
  return 0;
}

void KMeans::findClosestCentroids() {
}

void KMeans::computeCentroids() {
}

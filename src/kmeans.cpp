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

  cv::Mat output = proxy.kMeans(src, k, 1) ;
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
  cv::Mat memberships = cv::Mat::zeros(src.rows * src.cols, 1, CV_8UC1);

  // 1. Initialize Centroids
  proxy.initializeCentroids(src, centroids, k);

  // 2. Repeat:
  for(int i = 0; i < iter; i++) {
    // 1. Assign points to cluster centroids
    proxy.findClosestCentroids(src, centroids, memberships);

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

uchar KMeans::minIdx(const cv::Mat distances) {
  float minDist = distances.at<float>(0);
  uchar minId = 0;

  for(uchar i = 0; i < distances.rows; i++)
    if(distances.at<float>(i) < minDist) {
      minId = i;
      minDist = distances.at<float>(i);
    }

  return minId;
}

void KMeans::findClosestCentroids(const cv::Mat &src, const cv::Mat &centroids, cv::Mat &memberships) {
  KMeans proxy;
  cv::Mat distances = cv::Mat::zeros(centroids.rows, 1, CV_32FC1);

  for(int r = 0; r < src.rows; r++) {
    cv::Vec3b *row = (cv::Vec3b *) src.ptr<cv::Vec3b>(r);

    for(int c = 0; c < src.cols; c++) {
      for(int k = 0; k < centroids.rows; k++) distances.at<float>(k) = proxy.distance(row[c], centroids.at<cv::Vec3b>(k));

      memberships.at<uchar>((r * src.cols) + c) = proxy.minIdx(distances);
    }
  }
}

template<typename T>
float KMeans::distance(const T &pt1, const T &pt2) {
  if(pt1.channels != pt2.channels) return -1;

  float dist = 0;
  for(int i = 0; i < pt1.channels; i++) dist += (pt2[i] - pt1[i]) * (pt2[i] - pt1[i]);

  return sqrtf(dist);
}

void KMeans::computeCentroids(const cv::Mat &src, cv::Mat &centroids, const cv::Mat &memberships) {
}

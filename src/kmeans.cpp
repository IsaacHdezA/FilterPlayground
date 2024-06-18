#include <iostream>

#include "../include/kmeans.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat KMeans::applyFilter(const cv::Mat &src, int k, int iter) {
  KMeans proxy;

  return proxy.kMeans(src, k, iter);
}

cv::Mat KMeans::kMeans(const cv::Mat &src, int k, int iter) {
  KMeans proxy;
  std::vector<cv::Vec3b> centroids(k);
  std::vector<uchar> memberships(src.rows * src.cols, 0);

  // 1. Initialize Centroids
  proxy.initializeCentroids(src, centroids, k);

  // 2. Repeat:
  for(int i = 0; i < iter; i++) {
    // 1. Assign points to cluster centroids
    proxy.findClosestCentroids(src, centroids, memberships);

    // 2. Move cluster centroids
    proxy.computeCentroids(src, centroids, memberships);
  }

  return proxy.buildImage(src, centroids, memberships);
}

void KMeans::initializeCentroids(const cv::Mat &src, std::vector<cv::Vec3b> &centroids, int k) {
  KMeans proxy;

  for(int i = 0; i < k; i++) {
    int randY = proxy.randInt(0, src.rows),
        randX = proxy.randInt(0, src.cols);
    
    centroids[i] = src.at<cv::Vec3b>(randY, randX);
  }
}

void KMeans::findClosestCentroids(const cv::Mat &src, const std::vector<cv::Vec3b> &centroids, std::vector<uchar> &memberships) {
  KMeans proxy;
  std::vector<float> distances(centroids.size());

  for(int r = 0; r < src.rows; r++) {
    cv::Vec3b *row = (cv::Vec3b *) src.ptr<cv::Vec3b>(r);

    for(int c = 0; c < src.cols; c++) {
      for(int k = 0; k < centroids.size(); k++) distances[k] = proxy.distance(row[c], centroids[k]);

      memberships[(r * src.cols) + c] = proxy.minIdx(distances);
    }
  }
}

uchar KMeans::minIdx(const std::vector<float> distances) {
  float minDist = distances[0];
  int minId = 0;

  for(int i = 0; i < distances.size(); i++)
    if(distances[i] < minDist) {
      minId = i;
      minDist = distances[i];
    }

  return minId;
}

template<typename T>
float KMeans::distance(const T &pt1, const T &pt2) {
  if(pt1.channels != pt2.channels) return -1;

  float dist = 0;
  for(int i = 0; i < pt1.channels; i++) dist += (pt2[i] - pt1[i]) * (pt2[i] - pt1[i]);

  return sqrtf(dist);
}

void KMeans::computeCentroids(const cv::Mat &src, std::vector<cv::Vec3b> &centroids, const std::vector<uchar> &memberships) {
  for(int k = 0; k < centroids.size(); k++) {
    cv::Vec3f sums  = cv::Vec3f::zeros();
    unsigned long int count = 0;

    for(int r = 0; r < src.rows; r++) {
      for(int c = 0; c < src.cols; c++) {
        if(memberships[(r * src.cols) + c] == k) {
          cv::Vec3b point = src.at<cv::Vec3b>(r, c);

          for(int channel = 0; channel < src.channels(); channel++) sums[channel] += point[channel];
          count++;
        }
      }
    }

    for(int channel = 0; channel < src.channels(); channel++) centroids[k][channel] = (uchar) (sums[channel] / count);
  } 
}

cv::Mat KMeans::buildImage(const cv::Mat &src, const std::vector<cv::Vec3b> &centroids, const std::vector<uchar> &memberships) {
  cv::Mat output = src.clone();

  for(int r = 0; r < output.rows; r++) {
    cv::Vec3b *outputRow = output.ptr<cv::Vec3b>(r);

    for(int c = 0; c < output.rows; c++) {
      outputRow[c] = centroids[memberships[(r * src.cols) + c]];
    }
  }

  return output;
}
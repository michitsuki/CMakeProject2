#pragma once
#include <iostream>
#include "common.h"
#include <opencv2/opencv.hpp>
#include <random>
#include <functional>

struct Vec3bHash {
	std::size_t operator()(const cv::Vec3b& pixel) const {
		std::size_t seed = 0;
		for (int i = 0; i < 3; i++) {
			seed ^= std::hash<uchar>{}(pixel[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

class MarkovChain {
private:
	std::vector<std::vector<cv::Vec3b>> pixels;
	std::unordered_map<cv::Vec3b, std::vector<cv::Vec3b>, Vec3bHash> transitionMap;
	std::random_device rd;
	std::mt19937 gen;
public:
	MarkovChain(const std::vector<std::vector<cv::Vec3b>>& imagePixels) : pixels(imagePixels), gen(rd()) {
		buildTransitionMap();
	};
	void buildTransitionMap();
	cv::Vec3b getNextPixel(const cv::Vec3b& currentPixel);
};
#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "common.h"

class Image {
private:
	std::vector<std::vector<cv::Vec3b>> pixels;
public:
	Image(int w, int h);
	Image(std::string filename);
	void setPixel(int x, int y, u8 r, u8 g, u8 b);
	void display();
	std::vector<std::vector<cv::Vec3b>> getPixels();
};
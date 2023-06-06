#include "image.h"

std::vector<std::vector<cv::Vec3b>> pixels;

Image::Image(int w, int h) {
	pixels.resize(h, std::vector<cv::Vec3b>(w));
}

Image::Image(std::string filename) {
	cv::Mat image = cv::imread(filename);
	if (image.empty()) {
		// Handle error: Failed to load the image
		throw std::invalid_argument("Image not found");
	}

	pixels.resize(image.rows, std::vector<cv::Vec3b>(image.cols));
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
			pixels[i][j] = image.at<cv::Vec3b>(i, j); {
	}
}

void Image::setPixel(int x, int y, u8 r, u8 g, u8 b) {
	pixels[y][x] = cv::Vec3b(b, g, r);
}
void Image::display() {
	cv::Mat img(pixels.size(), pixels[0].size(), CV_8UC3); {
		for (int y = 0; y < pixels.size(); y++) {
			for (int x = 0; x < pixels[y].size(); x++) {
				img.at<cv::Vec3b>(y, x) = pixels[y][x];
			}
		}
		cv::imshow("Original Image", img);
		cv::waitKey(0);
	}
}
std::vector<std::vector<cv::Vec3b>> Image::getPixels() {
	return pixels;
}

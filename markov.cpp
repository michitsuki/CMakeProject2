#include "markov.h"

// Class for a markov chain based on the values of each pixel

void MarkovChain::buildTransitionMap() {
	const int height = pixels.size();
	const int width = pixels[0].size();
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width - 1; j++) {
			cv::Vec3b currentPixel = pixels[i][j];
			cv::Vec3b nextPixel = pixels[i][j + 1];
			std::cout << "Mapped " << currentPixel << " to next pixel " << nextPixel << "\n";
			transitionMap[currentPixel].push_back(nextPixel);
		}
	}
	// Flush buffer
	std::cout << std::endl;
}
cv::Vec3b MarkovChain::getNextPixel(const cv::Vec3b& currentPixel) {
	const auto& possiblePixels = transitionMap[currentPixel];
	// check for no possible nexts and set 0, 0, 0 if SET_BLACK is defined
	// else use random values
#ifdef SET_BLACK
	if (possiblePixels.size() < 1) {
		return cv::Vec3b(0, 0, 0);
	}
#endif
#ifndef SET_BLACK
	if (possiblePixels.size() < 1) {
		return cv::Vec3b(gen() % 255, gen() % 255, gen() % 255);
	}
#endif
	std::uniform_int_distribution<> distribution(0, possiblePixels.size() - 1);
	const int randomIndex = distribution(gen);
	return possiblePixels[randomIndex];
}


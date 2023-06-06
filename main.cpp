// main.cpp : Defines the entry point for the application.
//

#include "main.h"

using namespace std;

int main()
{
	// Create random generator
	random_device rd;
	mt19937 gen(rd());

	// Load image
	cout << "image: ";
	string imagename;
	cin >> imagename;
	Image source = Image(imagename);
	source.display();

	u32 width = source.getPixels()[0].size();
	u32 height = source.getPixels().size();

	// Create markov chain from image
	MarkovChain chain = MarkovChain(source.getPixels());
	Image result = Image(width, height);
	
	// Count number of same pixels to prevent infinite loops
	u64 samePixelsCount = 0;

	// Set up creation loop
	cv::Vec3b previous = NULL;
	cv::Vec3b start = source.getPixels()[0][0];
	cout << "Starting pixel: " << start << endl;

	for (u64 i = 0; i < height; i++) {
		for (u64 j = 0; j < width; j++) {
			result.setPixel(j, i, start[0], start[1], start[2]);
			// Uses \n so the application doesnt have to wait for the console to catch up
			cout << "Set pixel at: " << j << ", " << i << " to: " << start << "\n";
			previous = start;
			start = chain.getNextPixel(start);
			if (previous == start) {
				++samePixelsCount;
			}
			// If pixels are the same in a row 10 times pick a random pixel from the source
			if (samePixelsCount > 10) {
				start = source.getPixels()[gen() % height][gen() % width];
				samePixelsCount = 0;
				cout << "Loop detected, using " << start << " instead" << "\n";
			}
			cout << "Got next pixel: " << start << "\n";
		}
	}
	result.display();

	return 0;
}

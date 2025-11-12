/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"

Stats::Stats(PNG& im) { // i think this is to fill the rgb specs of the photo?
	/* Complete your implementation below */
	int width = im.width();
	int height = im.height();

	// they're vectors of vectors of ints
	sumRed.resize(width, vector<int64_t> (height, 0));
	sumGreen.resize(width, vector<int64_t> (height, 0));
	sumBlue.resize(width, vector<int64_t> (height, 0));

	sumsqRed.resize(width, vector<int64_t> (height, 0));
	sumsqGreen.resize(width, vector<int64_t> (height, 0));
	sumsqBlue.resize(width, vector<int64_t> (height, 0));

	// filling the 2d vectors
	for(int x = 0; x < width; x++) {
		for(int y=0;y<height;y++) {
			RGBAPixel* p = im.getPixel(x, y);
			int64_t r = p->r;
			int64_t g = p->g;
			int64_t b = p->b;

			// fill red
			
			// fill green

			// fill blue

			// fill r2

			// fill g2

			// fill b2
		}
	}
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
	int result = 0;

	// for(int i = 0; i < (w-pair.first); i++) {
	// 	for(int j = 0; j < (h-pair.second); j++) {
			
	// 	}
	// }

	return result;
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */
	return 0;
}

/**
 * Given a rectangle, compute its sum of squared deviations from mean, over all color channels.
 * See written specification for a description of this function.
**/
double Stats::GetVar(pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */
	return 0;
}


RGBAPixel Stats::GetAvg(pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */


	return RGBAPixel();
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/


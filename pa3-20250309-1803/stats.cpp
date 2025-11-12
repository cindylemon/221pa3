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

			int64_t r2 = r*r;
			int64_t g2 = g*g;
			int64_t b2 = b*b;

			// fill red
			int64_t redAbove = (y>0)? sumRed[x][y-1] : 0;
			int64_t redLeft = (x>0)? sumRed[x-1][y] : 0;
			int64_t redOverlap = (x>0 && y>0)? sumRed[x-1][y-1] : 0;
			sumRed[x][y] = r + redAbove + redLeft - redOverlap;

			// fill green
			int64_t greenAbove = (y>0)? sumGreen[x][y-1] : 0;
			int64_t greenLeft = (y>0)? sumGreen[x-1][y] : 0;
			int64_t greenOverlap = (x>0 && y>0)? sumGreen[x-1][y-1] : 0;
			sumGreen[x][y] = g + greenAbove + greenLeft - greenOverlap;

			// fill blue
			int64_t blueAbove = (y>0)? sumBlue[x][y-1] : 0;
			int64_t blueLeft = (x>0)? sumBlue[x][y-1] : 0;
			int64_t blueOverlap = (x>0 && y>0)? sumBlue[x-1][y-1] : 0;
			sumBlue[x][y] = b + blueAbove + blueLeft - blueOverlap;

			// fill redsq 
			int64_t redSqAbove = (y>0)? sumsqRed[x][y-1] : 0;
			int64_t redSqLeft = (x>0)? sumsqRed[x-1][y] : 0;
			int64_t redSqOverlap = (x>0 && y>0)? sumsqRed[x-1][y-1] : 0;
			sumsqRed[x][y] = r2 + redSqAbove + redSqLeft - redSqOverlap;

			// fill greensq
			int64_t greenSqAbove = (y>0)? sumsqGreen[x][y-1] : 0;
			int64_t greenSqLeft = (y>0)? sumsqGreen[x-1][y] : 0;
			int64_t greenSqOverlap = (x>0 && y>0)? sumsqGreen[x-1][y-1] : 0;
			sumsqGreen[x][y] = g2 + greenSqAbove + greenSqLeft - greenSqOverlap;

			// fill bluesq
			int64_t blueSqAbove = (y>0)? sumsqBlue[x][y-1] : 0;
			int64_t blueSqLeft = (x>0)? sumsqBlue[x][y-1] : 0;
			int64_t blueSqOverlap = (x>0 && y>0)? sumsqBlue[x-1][y-1] : 0;
			sumsqBlue[x][y] = r2 + blueSqAbove + blueSqLeft - blueSqOverlap;
		}
	}
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
	//int result = 0;
	int x = ul.first;
	int y = ul.second;

	int x2 = x + w - 1;
	int y2 = y + h - 1;

	vector<vector<int64_t>>* sum = nullptr;
	if(channel == 'r') sum = &sumRed;
	if(channel == 'g') sum = &sumGreen;
	if(channel == 'b') sum = &sumBlue;

	int64_t t = (*sum)[x2][y2];

	// subtract left and above, then re add the overlap
	if(x > 0) t = t-(*sum)[x-1][y2];
	if(y > 0) t = t-(*sum)[x2][y-1];
	if(y > 0 && x > 0) t = t + (*sum)[x-1][y-1];

	return t;
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
	int x = ul.first;
	int y = ul.second;

	int x2 = x + w - 1;
	int y2 = y + h - 1;

	vector<vector<int64_t>>* sum = nullptr;
	if(channel == 'r') sum = &sumsqRed;
	if(channel == 'g') sum = &sumsqGreen;
	if(channel == 'b') sum = &sumsqBlue;

	int64_t t = (*sum)[x2][y2];

	if(x > 0) t = t-(*sum)[x-1][y2];
	if(y > 0) t = t-(*sum)[x2][y-1];
	if(y > 0 && x > 0) t = t + (*sum)[x-1][y-1];

	return t;
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
	int64_t area = (int64_t)w*(int64_t)h;

	int64_t sumR = GetSum('r', ul, w, h);
	int64_t sumG = GetSum('g', ul, w, h);
	int64_t sumB = GetSum('b', ul, w, h);

	RGBAPixel p;
	p.r = sumR/area;
	p.g = sumG/area;
	p.b = sumB/area;

	return p;
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/


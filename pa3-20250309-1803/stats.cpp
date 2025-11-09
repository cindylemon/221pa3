/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"

Stats::Stats(PNG& im) {
	/* Complete your implementation below */

	
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
	/* Replace the line below with your implementation */
	return 0;
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


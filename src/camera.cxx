extern "C" {
#include <SDL.h>
}

#include "camera.hxx"

#include <algorithm>
#include <climits>
#include <cmath>

camera::camera(int displayWidth, int displayHeight)
: aspect((double)displayWidth/(double)displayHeight)
, displayHeight(displayHeight)
, leftMost(0)
, rightMost(0)
, topMost(0)
, bottMost(0)

// the transformation to apply
, scale(0)
, offsetX(0)
, offsetY(0)
{
}

void camera::clear()
{
	leftMost = INT_MAX;
	rightMost = INT_MIN;
	topMost = INT_MAX;
	bottMost = INT_MIN;
}


void camera::considerObject(int x, int y, int clearRadius)
{
	if (leftMost > x - clearRadius)
		leftMost = x - clearRadius;
	if (rightMost < x + clearRadius)
		rightMost = x + clearRadius;
	if (topMost > y - clearRadius)
		topMost = y - clearRadius;
	if (bottMost < y + clearRadius)
		bottMost = y + clearRadius;
}

void camera::calculateTransforms()
{
	// Fix aspect of the left/right/top/bottMost rectangle to match display aspect.
	// aspect_correction is the amount by which the width isn't wide enough
	int aspect_correction =
		aspect * (bottMost - topMost) // target width
		- (rightMost - leftMost); // actual object-encompassing width at the moment
	if (aspect_correction > 0)
	{
		rightMost += aspect_correction / 2;
		leftMost -= aspect_correction / 2 + aspect_correction % 2;
	}
	else
	{
		// apparently we're lacking in height instead.
		aspect_correction = (rightMost - leftMost) / aspect - (bottMost - topMost);
		bottMost += aspect_correction / 2;
		topMost -= aspect_correction / 2 + aspect_correction % 2;
	}

	scale = displayHeight / (double)(bottMost - topMost);
	offsetX = -leftMost;
	offsetY = -topMost;
}

bool camera::transform(SDL_Rect *r)
{
	r->x = (r->x + offsetX) * scale;
	r->y = (r->y + offsetY) * scale;
	r->w = r->w * scale;
	r->h = r->h * scale;

	// Calculate if the transformed object would appear on the display.
	// Be conservative because may be rotated.
	auto estimating_side_length = 2 * std::max(r->w, r->h);
	return r->x + estimating_side_length > 0
			&& r->y + estimating_side_length > 0
			&& r->x - estimating_side_length < aspect*displayHeight
			&& r->y - estimating_side_length < displayHeight;
}

camera::~camera()
{
}

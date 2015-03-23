#ifndef _TESTSDL_CAMERA_HXX
#define _TESTSDL_CAMERA_HXX

extern "C" {
#include <SDL.h>
}


class camera {
public:
	/**
	 * \brief
	 *   Initialize a camera for a particular display size.
	 */
	camera(int displayWidth, int displayHeight);
	/**
	 * \brief
	 *   Prepare the camera to consider objects. Call first before each frame.
	 */
	void clear();
	/**
	 * \brief
	 *   Pass the camera a circular area that needs to be visible on-screen. Call before calling calculateTransforms().
	 */
	void considerObject(int x, int y, int clearRadius);
	/**
	 * \brief
	 *   Computes transforms, call before calling transform() and after all your considerObject() calls.
	 */
	void calculateTransforms();
	/**
	 * \brief
	 *   Take a rect with game coordinates and translate them into display coordinates.
	 *
	 * This should be the function that gets called the most because all things
	 * to be drawn on-screen will need to be transformed first.
	 *
	 * \returns
	 *   true if the object would appear on the display.
	 */
	bool transform(SDL_Rect *r);
	virtual ~camera();
private:
	// display
	double aspect;
	int displayHeight;

	// again, in game units
	int leftMost;
	int rightMost;
	int topMost;
	int bottMost;

	// the transformation to apply
	double scale;
	double offsetX;
	double offsetY;
};

#endif 
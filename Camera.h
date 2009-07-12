/*
 * Camera.h
 *
 *  Created on: Jul 12, 2009
 *      Author: josh
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <highgui.h>
#include <cv.h>
#include "Pixel.h"
#include "LatLon.h"

class Camera
{
public:
	Camera(int index, const char* homographyFile, const char* inverseFile);
	Camera(const char* filename, const char* homographyFile, const char* inverseFile);
	virtual ~Camera();

	int grabFrame();
	IplImage* retrieveFrame();

	Pixel inViewLatLon(LatLon latlon);

private:
	CvCapture* capture;
	CvMat* homography;
	CvMat* inverse;
	double cameraWidth;
	double cameraHeight;
	double cameraFPS;

	void loadHomography(const char* homographyFile, const char* inverseFile);
	void getCameraProperties();
};

#endif /* CAMERA_H_ */

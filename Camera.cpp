/*
 * Camera.cpp
 *
 *  Created on: Jul 12, 2009
 *      Author: josh
 */

#include "Camera.h"

Camera::Camera(int index,
		const char* homographyFile,
		const char* inverseFile)
{
    if((capture = cvCreateCameraCapture(index)) == NULL)
    {
        printf("Error create camera capture for camera %d\n", index);
    }
	loadHomography(homographyFile, inverseFile);
	getCameraProperties();
}

Camera::Camera(const char* filename,
		const char* homographyFile,
		const char* inverseFile)
{
    if((capture = cvCreateFileCapture(filename)) == NULL)
    {
        printf("Error creating file capture for file %s\n", filename);
    }
	loadHomography(homographyFile, inverseFile);
	getCameraProperties();
}

Camera::~Camera()
{
	cvReleaseCapture(&capture);
	cvReleaseMat(&homography);
}

int Camera::grabFrame()
{
	return cvGrabFrame(capture);
}

QImage* Camera::retrieveFrame()
{
    IplImage* image = cvRetrieveFrame(capture);
    int width = image->width;
    int height = image->height;
    int pixels = width * height;
    uchar* imageData = new unsigned char[4 * pixels];
    for(int i = 0; i < pixels; i++)
    {
        imageData[i * 4 + 3] = 0xFF; // alpha channel
    }

    uchar* src = (uchar*)(image->imageData);
    uchar* srcEnd = src + (3 * pixels);
    uchar* dest = imageData;

    do
    {
        memcpy(dest, src, 3);
        dest += 4;
        src += 3;
    }
    while(src < srcEnd);

    QImage* result = new QImage(imageData, width, height, QImage::Format_RGB32);
    return result;
}

Pixel Camera::inViewLatLon(LatLon latlon)
{
	CvMat* latlonHomogeneous = cvCreateMat(3, 1, CV_32FC1);
	cvmSet(latlonHomogeneous, 0, 0, latlon.getLat());
	cvmSet(latlonHomogeneous, 1, 0, latlon.getLon());
	cvmSet(latlonHomogeneous, 2, 0, 1.0);

	CvMat* pixelHomogeneous = cvCreateMat(3, 1, CV_32FC1);

	cvMatMul(inverse, latlonHomogeneous, pixelHomogeneous);

	int x = (int)(cvmGet(pixelHomogeneous, 0, 0) / cvmGet(pixelHomogeneous, 2, 0));
	int y = (int)(cvmGet(pixelHomogeneous, 1, 0) / cvmGet(pixelHomogeneous, 2, 0));
	Pixel pixel(x, y);
	if(x < 0 || x > cameraWidth || y < 0 || y > cameraHeight)
	{
		pixel.setValid(false);
	}
	return pixel;
}

void Camera::loadHomography(const char* homographyFile,
		const char* inverseFile)
{
    if((homography = (CvMat*) cvLoad(homographyFile)) == NULL)
    {
        printf("Error loading %s\n", homographyFile);
    }
    if((inverse = (CvMat*) cvLoad(inverseFile)) == NULL)
    {
        printf("Error loading %s\n", inverseFile);
    }
}

void Camera::getCameraProperties()
{
	cameraWidth = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	cameraHeight = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	cameraFPS = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
}

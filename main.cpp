#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Pixel.h"
#include "LatLon.h"
#include "Camera.h"

#define NUM_CAMERAS 8

int main(int argc, char *argv[])
{
    Camera* cameras[NUM_CAMERAS];
    char* window_names[NUM_CAMERAS];

    char* filename = (char*) malloc(150);
    char* homographyFile = (char*) malloc(100);
    char* inverseFile = (char*) malloc(100);
    for (int i = 0; i < NUM_CAMERAS; i++)
    {
        sprintf(filename, "/home/josh/research/datasets/peachtree-arterial/raw-video-0400pm-0415pm/peachtree-camera%d-0400pm-0415pm.avi", (i+1));
        sprintf(homographyFile, "/home/josh/research/datasets/peachtree-arterial/peachtree-camera%d-homography.xml", (i+1));
        sprintf(inverseFile, "/home/josh/research/datasets/peachtree-arterial/peachtree-camera%d-inverse.xml", (i+1));

        cameras[i] = new Camera(filename, homographyFile, inverseFile);

        window_names[i] = (char*) malloc(20);
        sprintf(window_names[i], "Camera %d", (i + 1));
        cvNamedWindow(window_names[i], 1);

        // check for a latlon point
        LatLon latlon(33.784299,-84.383193);
        Pixel pixel = cameras[i]->inViewLatLon(latlon);
        if(pixel.isValid())
        {
            printf("Camera %d has %f, %f at pixel %d, %d\n",
                    (i+1), latlon.getLat(), latlon.getLon(),
                    pixel.getX(), pixel.getY());
        }
        else
        {
            printf("Camera %d does not have %f, %f\n",
                    (i+1), latlon.getLat(), latlon.getLon());
        }
    }

    IplImage* frame;
    char key = 0;
    while (key != 27)
    {
        key = cvWaitKey(10);

        for (int i = 0; i < NUM_CAMERAS; i++)
        {
            cameras[i]->grabFrame();
        }
        for (int i = 0; i < NUM_CAMERAS; i++)
        {
            frame = cameras[i]->retrieveFrame();
            cvShowImage(window_names[i], frame);
        }
    }

    for (int i = 0; i < NUM_CAMERAS; i++)
    {
        delete cameras[i];
    }
    cvDestroyAllWindows();
    return 0;


    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}

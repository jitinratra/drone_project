
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "string.h"
#include "stdio.h"
#include "UserInterface.h"
#include "CvImageViewer.h"
#include "HSVWidget.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent), m_capture(1)
{
	QWidget *w = new QWidget();
	hsv = new HSVWidget();
	p_camera_viewer = new CvImageViewer();
	p_camera_viewer->show();
	p_filtered_viewer = new CvImageViewer();
	p_filtered_viewer->show();
	p_eroded_viewer = new CvImageViewer();
	p_eroded_viewer->show();

	m_timer.setInterval(500);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
	m_timer.start();

	hsv->show();
	QVBoxLayout *vlay = new QVBoxLayout();
	QHBoxLayout *lay1 = new QHBoxLayout();
	QHBoxLayout *lay2 = new QHBoxLayout();
	p_erodeSlider = new QSlider();
	p_dilateSlider = new QSlider();
	p_erodeSlider->setOrientation(Qt::Horizontal);
	p_dilateSlider->setOrientation(Qt::Horizontal);
	p_erodeSlider->setRange(1, 20);
	p_dilateSlider->setRange(1, 20);
	vlay->addLayout(lay1);
	vlay->addLayout(lay2);
	lay1->addWidget(new QLabel("Erode"));
	lay1->addWidget(p_erodeSlider);
	lay2->addWidget(new QLabel("Dilate"));
	lay2->addWidget(p_dilateSlider);
	w->setLayout(vlay);

	this->setCentralWidget(w);
}


void UserInterface::refresh()
{
	Mat mat, filtered, eroded, contoursMat;
	Mat erodeKernel, dilateKernel;
	erodeKernel = getStructuringElement(MORPH_RECT, Size(p_erodeSlider->value(),p_erodeSlider->value()));
	dilateKernel = getStructuringElement(MORPH_RECT, Size(p_dilateSlider->value(),p_dilateSlider->value()));
	m_capture >> mat;
	inRange(mat, Scalar((double)hsv->getHMin(), (double)hsv->getSMin(), (double)hsv->getVMin()), Scalar((double)hsv->getHMax(), (double)hsv->getSMax(), (double)hsv->getVMax()), filtered); 
	erode(filtered, eroded, erodeKernel);
	erode(eroded, eroded, erodeKernel);
	dilate(eroded, eroded, dilateKernel);
	dilate(eroded, eroded, dilateKernel);

	std::vector< std::vector<Point> > contours;
	contoursMat = eroded.clone();
	findContours(contoursMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	int contoursNb = contours.size();
	int refArea = 0;
	int x = 0;
	int y = 0;
	bool found = false;
	char text[10];

	for(int i=0; i<contoursNb; i++)
	{
		Moments mom = moments(contours[i], false);
		double area = mom.m00;

		if(area > 800 && refArea < area)
		{
			refArea = area;
			y = mom.m01 / area;
			x = mom.m10 / area;
		}
	}
	if(refArea > 0.0){
		//printf("%ld, %ld\n", x, y);
		putText(mat, "O", Point(x, y), 2, 1, Scalar(255, 0,0), 2); 
	}
	sprintf(text, "%d", contoursNb);
	putText(mat, text, Point(10, 50), 2, 1, Scalar(255, 0,0), 2); 

	p_camera_viewer->showImage(mat);
	p_filtered_viewer->showImage(filtered);
	p_eroded_viewer->showImage(eroded);
}

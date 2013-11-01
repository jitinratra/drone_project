
#include "UserInterface.h"
#include "CvImageViewer.h"
#include "HSVWidget.h"

#include "opencv2/core/core.hpp"


UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent), m_capture(0)
{
	QWidget *w = new QWidget();
	hsv = new HSVWidget();
	p_camera_viewer = new CvImageViewer();
	p_camera_viewer->show();
	p_filtered_viewer = new CvImageViewer();
	p_filtered_viewer->show();

	m_timer.setInterval(200);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
	m_timer.start();

	hsv->show();
	this->setCentralWidget(w);
}


void UserInterface::refresh()
{
	Mat mat, filtered;
	m_capture >> mat;
	inRange(mat, Scalar((double)hsv->getHMin(), (double)hsv->getSMin(), (double)hsv->getVMin()), Scalar((double)hsv->getHMax(), (double)hsv->getSMax(), (double)hsv->getVMax()), filtered); 
	p_camera_viewer->showImage(mat);
	p_filtered_viewer->showImage(filtered);
}

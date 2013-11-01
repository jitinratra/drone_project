
#include "UserInterface.h"
#include "CvImageViewer.h"
#include "CvVideoViewer.h"

#include "opencv2/core/core.hpp"


using namespace cv;

UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent)
{
	p_viewer = new CvVideoViewer(this);

	this->setCentralWidget(p_viewer);
}

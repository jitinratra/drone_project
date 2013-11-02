
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#include "HSVWidget.h"

class CvImageViewer;
class CvVideoViewer;

using namespace cv;


class UserInterface : public QMainWindow
{
	Q_OBJECT
public:
	UserInterface(QWidget *parent = 0);

public slots:
	void refresh();

private:
	VideoCapture m_capture;
	QTimer m_timer;
	CvImageViewer *p_camera_viewer;
	CvImageViewer *p_filtered_viewer;
	HSVWidget *hsv;
};

#endif

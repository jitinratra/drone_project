
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>

class CvImageViewer;
class CvVideoViewer;

class UserInterface : public QMainWindow
{
public:
	UserInterface(QWidget *parent = 0);

private:
	QLabel *p_imgViewer;
	CvVideoViewer *p_viewer;
};

#endif

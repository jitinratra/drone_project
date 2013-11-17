
#include "HSVWidget.h"

#include <QSlider>
#include <QBoxLayout>
#include <QLabel>


HSVWidget::HSVWidget(QWidget *parent) : QWidget(parent)
{
	Qt::Orientation orientation = Qt::Horizontal;
	p_hmin_slider = new QSlider();
	p_hmax_slider = new QSlider();
	p_smin_slider = new QSlider();
	p_smax_slider = new QSlider();
	p_vmin_slider = new QSlider();
	p_vmax_slider = new QSlider();
	p_hmin_slider->setOrientation(orientation);
	p_hmax_slider->setOrientation(orientation);
	p_smin_slider->setOrientation(orientation);
	p_smax_slider->setOrientation(orientation);
	p_vmin_slider->setOrientation(orientation);
	p_vmax_slider->setOrientation(orientation);

	QLabel *p_hmin_label = new QLabel("H_MIN");
	QLabel *p_hmax_label = new QLabel("H_MAX");
	QLabel *p_smin_label = new QLabel("S_MIN");
	QLabel *p_smax_label = new QLabel("S_MAX");
	QLabel *p_vmin_label = new QLabel("V_MIN");
	QLabel *p_vmax_label = new QLabel("V_MAX");

	p_hmin_slider->setRange(0,255);
	p_hmax_slider->setRange(0,255);
	p_hmax_slider->setValue(255);
	p_smin_slider->setRange(0,255);
	p_smax_slider->setRange(0,255);
	p_smax_slider->setValue(255);
	p_vmin_slider->setRange(0,255);
	p_vmax_slider->setRange(0,255);
	p_vmax_slider->setValue(255);

	QVBoxLayout *main_vbox;
	QHBoxLayout *hmin_vbox, *smin_vbox, *vmin_vbox;
	QHBoxLayout *hmax_vbox, *smax_vbox, *vmax_vbox;

	main_vbox = new QVBoxLayout();
	hmin_vbox = new QHBoxLayout();
	smin_vbox = new QHBoxLayout();
	vmin_vbox = new QHBoxLayout();
	hmax_vbox = new QHBoxLayout();
	smax_vbox = new QHBoxLayout();
	vmax_vbox = new QHBoxLayout();

	
	main_vbox->addLayout(hmin_vbox);
	main_vbox->addLayout(hmax_vbox);
	main_vbox->addLayout(smin_vbox);
	main_vbox->addLayout(smax_vbox);
	main_vbox->addLayout(vmin_vbox);
	main_vbox->addLayout(vmax_vbox);

	hmin_vbox->addWidget(p_hmin_label);
	hmin_vbox->addWidget(p_hmin_slider);
	
	hmax_vbox->addWidget(p_hmax_label);
	hmax_vbox->addWidget(p_hmax_slider);

	smin_vbox->addWidget(p_smin_label);
	smin_vbox->addWidget(p_smin_slider);

	smax_vbox->addWidget(p_smax_label);
	smax_vbox->addWidget(p_smax_slider);

	vmin_vbox->addWidget(p_vmin_label);
	vmin_vbox->addWidget(p_vmin_slider);

	vmax_vbox->addWidget(p_vmax_label);
	vmax_vbox->addWidget(p_vmax_slider);
	

	this->setLayout(main_vbox);

	connect(p_hmin_slider, SIGNAL(valueChanged(int)), this, SIGNAL(hmin_changed(int)));
	connect(p_hmax_slider, SIGNAL(valueChanged(int)), this, SIGNAL(hmax_changed(int)));
	connect(p_smin_slider, SIGNAL(valueChanged(int)), this, SIGNAL(smin_changed(int)));
	connect(p_smax_slider, SIGNAL(valueChanged(int)), this, SIGNAL(smax_changed(int)));
	connect(p_vmin_slider, SIGNAL(valueChanged(int)), this, SIGNAL(vmin_changed(int)));
	connect(p_vmax_slider, SIGNAL(valueChanged(int)), this, SIGNAL(vmax_changed(int)));
}

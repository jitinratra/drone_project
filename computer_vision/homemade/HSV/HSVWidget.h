
#ifndef HSV_WIDGET_H
#define HSV_WIDGET_H

#include <QWidget>
#include <QSlider>

class HSVWidget : public QWidget
{
	Q_OBJECT
public:
	HSVWidget(QWidget *parent = 0);

	int getHMin() const { return p_hmin_slider->value(); }
	int getHMax() const { return p_hmax_slider->value(); }
	int getSMin() const { return p_smin_slider->value(); }
	int getSMax() const { return p_smax_slider->value(); }
	int getVMin() const { return p_vmin_slider->value(); }
	int getVMax() const { return p_vmax_slider->value(); }

signals:
	void hmin_changed(int val);
	void smin_changed(int val);
	void vmin_changed(int val);
	void hmax_changed(int val);
	void smax_changed(int val);
	void vmax_changed(int val);

private:
	QSlider *p_hmin_slider, *p_hmax_slider;
	QSlider *p_smin_slider, *p_smax_slider;
	QSlider *p_vmin_slider, *p_vmax_slider;
};

#endif 


QT += core widgets

LIBS += -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab 

INCLUDEPATH += -I/usr/include/opencv 

SOURCES = main.cpp \
	UserInterface.cpp \
	HSVWidget.cpp

HEADERS = UserInterface.h \
		CvImageViewer.h \
		Image.h \
		ImageAlgorithm.h \
		HSVWidget.h

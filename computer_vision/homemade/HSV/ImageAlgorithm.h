

#ifndef IMAGE_ALGORITHM_H
#define IMAGE_ALGORITHM_H

#include <QList>
#include <QMap>
#include <QVariant>
#include <QString>

#include <opencv2/core/core.hpp>

class ImageAlgorithm
{
public:
	virtual Mat exec(const QList<Mat> &images, const QMap<QString, QVariant> &params) = 0;

};

#endif

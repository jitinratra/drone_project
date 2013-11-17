
#include <QApplication>
#include "UserInterface.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	UserInterface inter;
	inter.show();

	return app.exec();
}

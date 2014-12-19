#include "SerialPortDisplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	SerialPortDisplayer w;
	w.show();

	return a.exec();
}

#ifndef SERIALPORTDISPLAYER_H
#define SERIALPORTDISPLAYER_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStandardItemModel>

#include "ui_SerialPortDisplayer.h"

class SerialPortDisplayer : public QMainWindow, public Ui::SerialPortDisplayer
{
	Q_OBJECT

	public :
		explicit SerialPortDisplayer(QWidget *parent = 0);
		~SerialPortDisplayer();

	public slots :
		void refresh();
		void openSelected();
		void readOpened();

	private :
		QSerialPortInfo getSelectedPortInfo(bool& ok);

		QStandardItemModel * model;
		QList<QSerialPortInfo> portInfoList;
		QSerialPort currentPort;
};

#endif // SERIALPORTDISPLAYER_H

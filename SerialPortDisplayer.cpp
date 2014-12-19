#include "SerialPortDisplayer.h"

#include <QMessageBox>

SerialPortDisplayer::SerialPortDisplayer(QWidget *parent)
				   : QMainWindow(parent), model(new QStandardItemModel(10, 5, this))
{
	this->setupUi(this);

	TableView_Ports->setSelectionMode(QAbstractItemView::SingleSelection);
	TableView_Ports->setModel(model);
	model->setItem(0, 0, new QStandardItem("Port name :"));
	model->setItem(0, 1, new QStandardItem("Description :"));
	model->setItem(0, 2, new QStandardItem("Manufacturer :"));

	this->refresh();

	connect(PshBtn_Refresh, SIGNAL(clicked()), this, SLOT(refresh()));
	connect(PshBtn_OpenSelected, SIGNAL(clicked()), this, SLOT(openSelected()));
	connect(PshBtn_ReadOpened, SIGNAL(clicked()), this, SLOT(readOpened()));
}

SerialPortDisplayer::~SerialPortDisplayer() {}

void SerialPortDisplayer::refresh()
{
	portInfoList = QSerialPortInfo::availablePorts();

	int i = 0;
	for(QSerialPortInfo& spi : portInfoList)
	{
		if(i >= model->rowCount())
			break;

		model->setItem(i+1, 0, new QStandardItem(spi.portName()));
		model->setItem(i+1, 1, new QStandardItem(spi.description()));
		model->setItem(i+1, 2, new QStandardItem(spi.manufacturer()));

		i++;
	}
}

QSerialPortInfo SerialPortDisplayer::getSelectedPortInfo(bool& ok)
{
	QSerialPortInfo portInfo;
	ok = true;

	QItemSelectionModel * selection = TableView_Ports->selectionModel();
	if(!selection->currentIndex().isValid())
	{
		QMessageBox::warning(this, "No selection", "Select a port before opening it.");
		ok = false;
	}
	else
	{
		QModelIndex modelIndex = selection->currentIndex();
		if(modelIndex.row() < 1 || modelIndex.row() > portInfoList.size())
		{
			QMessageBox::warning(this, "Bad selection", "Invalid selection (header or empty row has been selected).");
			ok = false;
		}
		else
			portInfo = portInfoList.at(modelIndex.row()-1);
	}

	return portInfo;
}

void SerialPortDisplayer::openSelected()
{
	bool ok;
	QSerialPortInfo portInfo = this->getSelectedPortInfo(ok);
	if(!ok)	return;

	// portInfoList.at(modelIndex.row()-1);

	if(currentPort.isOpen())
		currentPort.close();

	currentPort.setPort(portInfo);
	if(currentPort.open(QIODevice::ReadOnly))
		QMessageBox::information(this, "Port opened", "The port " + portInfo.portName() + " has been successfully opened.");
	else
		QMessageBox::warning(this, "Failure", "Opening port " + portInfo.portName() + " failed : " + currentPort.errorString());
}

void SerialPortDisplayer::readOpened()
{
	if(!currentPort.isOpen())
	{
		QMessageBox::warning(this, "No port opened", "The port must be opened.");
		return;
	}

	QByteArray data = currentPort.readAll();
	QMessageBox::information(this, "Data read", "Data got by reading the port :\n" + QString(data.toStdString().c_str()));
}

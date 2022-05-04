#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "knobdriver.h"

#include <shv/coreqt/log.h>

using namespace shv::chainpack;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	new KnobDriver(ui->frameAR, "shv/mzapoknobs/a/knob_r/value");

}

MainWindow::~MainWindow()
{
	delete ui;
}



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
	new KnobDriver(ui->frameAG, "shv/mzapoknobs/a/knob_g/value");
	new KnobDriver(ui->frameAB, "shv/mzapoknobs/a/knob_b/value");
	new KnobDriver(ui->frameBR, "shv/mzapoknobs/b/knob_r/value");
	new KnobDriver(ui->frameBG, "shv/mzapoknobs/b/knob_g/value");
	new KnobDriver(ui->frameBB, "shv/mzapoknobs/b/knob_b/value");
}

MainWindow::~MainWindow()
{
	delete ui;
}



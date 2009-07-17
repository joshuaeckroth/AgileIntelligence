#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RenderArea.h"
#include "ProcessingController.h"
#include <QFileDialog>

MainWindow::MainWindow(int numCameras, int gridX, int gridY, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    RenderArea* renderArea = new RenderArea(this, numCameras, gridX, gridY);
    ui->verticalLayout->insertWidget(0, renderArea);

    processingController = new ProcessingController(renderArea, numCameras);

    connect(ui->actionStart, SIGNAL(clicked()), this, SLOT(startProcessing()));
    connect(ui->actionStop, SIGNAL(clicked()), this, SLOT(stopProcessing()));
    connect(ui->loadAois, SIGNAL(clicked()), this, SLOT(loadAois()));
    connect(ui->clearAois, SIGNAL(clicked()), this, SLOT(clearAois()));

    connect(processingController, SIGNAL(statusChange(bool, int, double)),
            this, SLOT(statusChange(bool, int, double)));

    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startProcessing()
{
    processingController->startProcessing();
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(true);
}

void MainWindow::stopProcessing()
{
    processingController->stopProcessing();
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);
}

void MainWindow::loadAois()
{
    QString aoiFile = QFileDialog::getOpenFileName(this, "Load Areas of Interest",
                                                   "/home/josh", "ESRI Shapefiles (*.shp)");
    if(!aoiFile.isNull())
    {
        processingController->loadAois(aoiFile);
    }
}

void MainWindow::clearAois()
{
    processingController->clearAois();
}

void MainWindow::statusChange(bool capturing, int frameNumber, double frameTime)
{
    QString msg;
    if(capturing) { msg += QString("Capturing... "); }
    else { msg += QString("Not capturing. "); }

    msg += QString("Frame ") + QString::number(frameNumber);
    msg += QString(", ");
    msg += QString::number(frameTime, 'f', 1);
    msg += QString(" secs");

    ui->statusbar->showMessage(msg);
}

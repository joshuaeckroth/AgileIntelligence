#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class ProcessingController;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int numCameras, int gridX, int gridY, QWidget* parent = 0);
    ~MainWindow();

private slots:
    void startProcessing();
    void stopProcessing();
    void statusChange(bool, int, double);

private:
    Ui::MainWindow* ui;
    ProcessingController* processingController;
};

#endif // MAINWINDOW_H

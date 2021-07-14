#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "tarkovloganalyser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_logPathButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::MainWindow *_ui;
    TarkovLogAnalyser _log_analyser;

    void resetLogTable();
};
#endif // MAINWINDOW_H

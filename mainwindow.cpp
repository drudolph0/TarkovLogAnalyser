#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _log_analyser = TarkovLogAnalyser();
}

MainWindow::~MainWindow()
{
    delete _ui;
}


void MainWindow::on_logPathButton_clicked()
{
    QString text = QFileDialog::getExistingDirectory(this,tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    _ui->logPathField->setText(text);
}


void MainWindow::on_updateButton_clicked()
{
    QString logPath = _ui->logPathField->toPlainText();
    if(logPath == "") {
        _ui->logView->setText("Log Path is empty.");
        return;
    }

    _ui->logView->setText("update");
    _ui->logView->setText(_log_analyser.analyse_log(logPath));
}


#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    resetLogTable();
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
    _ui->logTableWidget->clearContents();
    if(logPath == "") {
        return;
    }

    _ui->logTableWidget->setItem(0, 0, new QTableWidgetItem("Updating...."));

    auto logs = _log_analyser.analyse_log(logPath);
    _ui->logTableWidget->setRowCount(logs.size());
    for(int i = 0; i < logs.size(); ++i)
    {
        const auto& log = logs[i];
        _ui->logTableWidget->setItem(i, 0, new QTableWidgetItem(log.getTime()));
        _ui->logTableWidget->setItem(i, 1, new QTableWidgetItem(log.getIp()));
        _ui->logTableWidget->setItem(i, 2, new QTableWidgetItem(log.getPort()));
        _ui->logTableWidget->setItem(i, 3, new QTableWidgetItem(log.getCity()));
        _ui->logTableWidget->setItem(i, 4, new QTableWidgetItem(log.getCountry()));
        _ui->logTableWidget->setItem(i, 5, new QTableWidgetItem(log.getLocation()));
    }
}

void MainWindow::resetLogTable()
{
    QStringList header;
    header<< "Time" << "Ip" << "Port" << "City" << "Country" << "Map";
    _ui->logTableWidget->clearContents();
    _ui->logTableWidget->setHorizontalHeaderLabels(header);
    _ui->logTableWidget->setShowGrid(true);
    _ui->logTableWidget->setColumnWidth(0, 150);
    _ui->logTableWidget->setColumnWidth(2, 70);

}


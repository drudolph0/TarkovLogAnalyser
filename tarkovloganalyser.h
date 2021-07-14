#ifndef TARKOVLOGANALYSER_H
#define TARKOVLOGANALYSER_H

#include <QtNetwork>

#include "logdata.h"

class TarkovLogAnalyser
{
public:
    TarkovLogAnalyser();
    QString analyse_log(QString logpath);

private:
    QNetworkAccessManager *_manager;
};

#endif // TARKOVLOGANALYSER_H

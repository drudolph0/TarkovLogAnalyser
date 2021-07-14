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
    static const int LOG_COUNT = 20;
};

#endif // TARKOVLOGANALYSER_H

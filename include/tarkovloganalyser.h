#ifndef TARKOVLOGANALYSER_H
#define TARKOVLOGANALYSER_H

#include <QtNetwork>

#include "logdata.h"

class TarkovLogAnalyser
{
public:
    TarkovLogAnalyser();
    QVector<LogData> analyse_log(QString logpath);

private:
    QNetworkAccessManager *_manager;
    static const int LOG_COUNT = 40;
};

#endif // TARKOVLOGANALYSER_H

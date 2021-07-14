#ifndef LOGDATA_H
#define LOGDATA_H

#include <QString>

class LogData
{
public:
    LogData(QString time, QString ip, QString city, QString country, QString location);
    QString toQString();

private:
    QString _time;
    QString _ip;
    QString _city;
    QString _country;
    QString _location;
    QString delimeter = "\t";
};

#endif // LOGDATA_H

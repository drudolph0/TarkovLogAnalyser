#ifndef LOGDATA_H
#define LOGDATA_H

#include <QString>

class LogData
{
public:
    LogData(QString time, QString ip, QString port, QString city, QString country, QString location);
    QString toQString();

    QString getTime() const { return _time; }
    QString getIp() const { return _ip; }
    QString getPort() const { return _port; }
    QString getCity() const { return _city; }
    QString getCountry() const { return _country; }
    QString getLocation() const { return _location; }

    bool operator<(const LogData &logData) const
    {
        return(this->_time < logData.getTime());
    }

    bool operator>(const LogData &logData) const
    {
        return !(*this < logData);
    }

private:
    QString _time;
    QString _ip;
    QString _port;
    QString _city;
    QString _country;
    QString _location;
    QString delimeter = "\t";
};

#endif // LOGDATA_H

#include "include/logdata.h"

LogData::LogData(QString time, QString ip, QString port, QString city, QString country, QString location) :
    _time(time), _ip(ip), _port(port), _city(city), _country(country), _location(location)
{

}

QString LogData::toQString()
{
    return "time: " + _time + delimeter + _ip + delimeter + _port + delimeter + _city + "/" + _country + delimeter + _location;
}

#include "include/tarkovloganalyser.h"

#include <QDir>
#include <QFile>

TarkovLogAnalyser::TarkovLogAnalyser()
{
    _manager = new QNetworkAccessManager();
}

QVector<LogData> TarkovLogAnalyser::analyse_log(QString logpath) {
    QVector<LogData> logs;
    QDir dir(logpath);
    for(int i=dir.entryInfoList().size(); i > 0; --i)
    {
        auto curent = dir.entryInfoList().at(i - 1);
        QFile trace(curent.filePath() + QString("/" + curent.fileName().remove(0, 4) + " traces.log"));
        if(!trace.exists())
            continue;

        if (trace.open(QIODevice::ReadOnly))
        {
            QTextStream in(&trace);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(line.contains("Ip: "))
                {
                    auto split = line.split(",");
                    auto info = split[0].split("|")[0].split("+")[0].trimmed();
                    auto ip = split[2].split(":")[1].trimmed();
                    auto port = split[3].split(":")[1].trimmed();
                    auto location = split[4].split(":")[1].trimmed();

                    LogData log(info, ip, port, QString(""), QString(""), location);
                    logs.append(log);
                }
            }
            trace.close();
        }
        if(logs.size() > LOG_COUNT)
            break;
    }

    // batch query
    QUrl url("http://ip-api.com/batch");
    QByteArray postData;
    postData.append("[");
    for (auto it = logs.begin(); it != logs.end(); ++it)
    {
        postData.append("\"" + it->getIp().toStdString() + "\"");
        if(it != logs.end() - 1)
            postData.append(",");
    }
    postData.append("]");

    QNetworkRequest request(url);
    QNetworkReply *reply = _manager->post(request, postData);

    while (!reply->isFinished())
        qApp->processEvents();

    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);

    for (int i = 0; i < logs.size(); ++i)
    {
        if(json[i]["query"] == logs[i].getIp())
        {
            logs[i].setCity(json[i]["city"].toString());
            logs[i].setCountry(json[i]["country"].toString());
        }
    }

    std::sort(logs.begin(), logs.end(), std::greater<LogData>());

    return logs;
}

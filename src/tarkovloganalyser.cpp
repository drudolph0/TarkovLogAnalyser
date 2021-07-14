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
                    auto info = split[0].split("|")[0].trimmed();
                    auto ip = split[2].split(":")[1].trimmed();
                    auto port = split[3].split(":")[1].trimmed();
                    auto location = split[4].split(":")[1].trimmed();

                    QUrl url("http://ip-api.com/json/" + ip);
                    QNetworkRequest request(url);
                    QNetworkReply *reply = _manager->get(request);
                    while (!reply->isFinished())
                        qApp->processEvents();

                    QByteArray response_data = reply->readAll();
                    QJsonDocument json = QJsonDocument::fromJson(response_data);
                    auto city = json["city"].toString();
                    auto country = json["country"].toString();

                    LogData log(info, ip, port, city, country, location);
                    logs.append(log);
                    reply->deleteLater();
                }
            }
            trace.close();
        }
        if(logs.size() > 45)
            break;
    }

    std::sort(logs.begin(), logs.end(), std::greater<LogData>());

    return logs;
}

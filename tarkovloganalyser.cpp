#include "tarkovloganalyser.h"

#include <QDir>
#include <QFile>

TarkovLogAnalyser::TarkovLogAnalyser()
{
    _manager = new QNetworkAccessManager();
}

QString TarkovLogAnalyser::analyse_log(QString logpath) {
    QList<LogData> logs;
    QDir dir(logpath);
    //    auto last = dir.entryInfoList().at(dir.entryInfoList().size() - 1);
    auto last = dir.entryInfoList().at(33);
    QFile trace(last.filePath() + QString("/" + last.fileName().remove(0, 4) + " traces.log"));
    if(!trace.exists())
        return QString("no valid Logs.");

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

                LogData log(info, ip, city, country, location);
                logs.append(log);
                reply->deleteLater();
            }
        }
        trace.close();
    }
    QString out;

    for(auto log : logs)
    {
        out += log.toQString() + "\n";
    }

    return out;
}

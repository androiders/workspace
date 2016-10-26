#include "stockdatafilestorage.h"
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>

StockDataFileStorage::StockDataFileStorage(QObject *parent) : QObject(parent)
{

}

bool StockDataFileStorage::saveStockData(const QString &symbol, const QString &jsonData)
{
    QString homeDirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir homeDir(homeDirStr);

    QString symbPath = homeDir.absoluteFilePath(symbol);

    QFile stockFile(symbPath);
    if(!stockFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    stockFile.write(jsonData.toUtf8());
    stockFile.close();
    return true;

}

bool StockDataFileStorage::saveStockData(const QString &symbol, const QJsonArray &jsonData)
{
    QJsonDocument doc(jsonData);

    return saveStockData(symbol,doc.toJson());
}

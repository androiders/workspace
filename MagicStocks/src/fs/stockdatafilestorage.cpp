#include "stockdatafilestorage.h"
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>
#include "src/factories/stockdatafactory.h"

StockDataFileStorage::StockDataFileStorage(QObject *parent) : QObject(parent)
{

}

bool StockDataFileStorage::saveIndex(const StockModel *model, const QString & indexName)
{
    //QString indexPath = getHomeFilePath(indexName);
    QDir dir(indexName);
    if(model->rowCount() == 0)
        return false;

    QFile indexFile(dir.absolutePath());
    if(!indexFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    for(int i = 0; i < model->rowCount(); ++i)
    {

        const StockData & sd = model->getStockDataRef(i);
        indexFile.write(sd.symbol().toUtf8());
        indexFile.putChar('\n');
        //QDir dir(indexPath);
        QDir d = QFileInfo (indexName).absoluteDir();
        QJsonDocument doc(StockDataFactory::buildJsonFromStockData(&sd));
        saveStockData(d.absolutePath(),sd.symbol(),doc.toJson());
    }

    indexFile.close();
    return true;

}

bool StockDataFileStorage::saveStockData(const StockData  *data)
{
    return saveStockData(data->symbol(),StockDataFactory::buildJsonFromStockData(data));
}

bool StockDataFileStorage::saveStockData(const QString &symbol, const QString &jsonData)
{
    QString symbPath = getHomeFilePath(symbol);

    return saveStockData(symbPath,symbol,jsonData);
}

bool StockDataFileStorage::saveStockData(const QString &symbol, const QJsonArray &jsonData)
{
    QJsonDocument doc(jsonData);

    return saveStockData(symbol,doc.toJson());
}

bool StockDataFileStorage::saveStockData(const QString &dirPath, const QString &symbol, const QString &jsonData)
{
    QDir dir(dirPath);
    QString file = dir.filePath(symbol);
    QFile stockFile(file);
    if(!stockFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    stockFile.write(jsonData.toUtf8());
    stockFile.close();
    return true;
}

QString StockDataFileStorage::getHomeFilePath(const QString &fileName)
{
    QString homeDirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir homeDir(homeDirStr);

    QString symbPath = homeDir.absoluteFilePath(fileName);

    return symbPath;
}

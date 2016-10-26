#ifndef STOCKDATAFILESTORAGE_H
#define STOCKDATAFILESTORAGE_H

#include <QObject>
#include <QJsonArray>

class StockDataFileStorage : public QObject
{
    Q_OBJECT
public:
    explicit StockDataFileStorage(QObject *parent = 0);

signals:

public slots:

    bool saveStockData(const QString & symbol, const QString & jsonData);
    bool saveStockData(const QString & symbol, const QJsonArray & jsonData);

};

#endif // STOCKDATAFILESTORAGE_H

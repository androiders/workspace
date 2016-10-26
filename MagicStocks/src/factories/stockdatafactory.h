#ifndef STOCKDATAFACTORY_H
#define STOCKDATAFACTORY_H

#include <QObject>
#include "stockdata.h"
#include "stockmodel.h"

class StockDataFactory : public QObject
{
    Q_OBJECT
public:
    explicit StockDataFactory(QObject *parent = 0);

    void setModel(StockModel * model);

signals:

public slots:

    void buildFromJsonArray(const QJsonArray & array);

private:

    StockModel * mModel;
};

#endif // STOCKDATAFACTORY_H

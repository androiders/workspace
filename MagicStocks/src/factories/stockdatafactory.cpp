#include "stockdatafactory.h"

StockDataFactory::StockDataFactory(QObject *parent) : QObject(parent)
{

}

void StockDataFactory::setModel(StockModel *model)
{
    mModel = model;
}

void StockDataFactory::buildFromJsonArray(const QJsonArray &array)
{
    StockData * sd;
    for(int i = 0; i < array.size(); ++i)
    {
        sd = new StockData(array.at(i).toObject());
        mModel->addData(sd);
    }
}


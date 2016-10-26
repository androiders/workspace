#include "stockdatafactory.h"

StockDataFactory::StockDataFactory(QObject *parent) : QObject(parent)
{

}

void StockDataFactory::setModel(StockModel *model)
{
    mModel = model;
}

const QJsonArray StockDataFactory::buildJsonFromStockData(const StockData *sd)
{
    QJsonArray arr;
    if(!sd)
        return arr;

    for(int i = 0; i < sd->getHistoricalSize(); ++i)
    {
        QJsonObject jsonData;
        StockHistoricalDataPoint shdp = sd->getHistoricalData(i);
        jsonData["Symbol"] = shdp.getSymbol();
        jsonData["Close"] = shdp.closePrice();
        jsonData["Low"] = shdp.dayLow();
        jsonData["High"] = shdp.dayHigh();
        jsonData["Open"] = shdp.dayHigh();
        jsonData["Date"] = shdp.getDate().toString(Qt::ISODate);

        arr.append(jsonData);
    }

    return arr;
}

void StockDataFactory::buildFromJsonArray(const QJsonArray &array)
{
    StockData * sd;
    for(int i = 0; i < array.size(); ++i)
    {
        QJsonObject obj = array.at(i).toObject();
        sd = new StockData(obj.value("Name").toString(),obj.value("Symbol").toString());
        mModel->addData(sd);
    }
}

void StockDataFactory::buildHistoryFromJsonArray(const QString & symbol, const QJsonArray &array)
{
    StockData * sd = mModel->getStockData(symbol);
    if(!sd)
        return;

    StockHistoricalData shd;
    for(int i = 0; i < array.size(); ++i)
    {
        QJsonObject jsonData = array.at(i).toObject();
        QString symbol = jsonData["Symbol"].toString();
        float closePrice = jsonData["Close"].toString().toFloat();
        float open = jsonData["Open"].toString().toFloat();
        float dayLow = jsonData["Low"].toString().toFloat();
        float dayHigh = jsonData["High"].toString().toFloat();
        QDate date = QDate::fromString(jsonData["Date"].toString(),Qt::ISODate);

        StockHistoricalDataPoint shdp = createDataPoint(symbol,closePrice,open,dayLow,dayHigh, date);
        shd.addData(shdp);
    }

    sd->setHistoricalData(shd);
}

StockHistoricalDataPoint StockDataFactory::createDataPoint(QString symbol, float closePrice, float open, float dayLow, float dayHigh,QDate & date)
{
    StockHistoricalDataPoint shdp;
    shdp.setSymbol(symbol);
    shdp.setOpenPrice(open);
    shdp.setClosePrice(closePrice);
    shdp.setDayLow(dayLow);
    shdp.setDayHigh(dayHigh);
    shdp.setDate(date);
  //  shdp.setSma200(sma200);

    return shdp;
}

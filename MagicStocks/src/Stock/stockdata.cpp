#include "stockdata.h"


StockData::StockData(QObject *parent) : QObject(parent)
{
    dayLow = 0.0f;
    dayHigh = 500.0f;
    change = 0.f;
}

StockData::StockData(const QJsonObject &jsonData)
{
    mName = jsonData["Name"].toString();
    mSymbol = jsonData["Symbol"].toString();
    currentPrice = (jsonData["Bid"].toString()).toFloat();
    dayLow = (jsonData["DaysLow"].toString()).toFloat();
    dayHigh = (jsonData["DaysHigh"].toString()).toFloat();
    change = (jsonData["Change"].toString()).toFloat();

    twoHundredDayAverage = (jsonData["TwoHundreddayMovingAverage"].toString()).toFloat();
    fiftyDayAverage = (jsonData["FiftydayMovingAverage"].toString()).toFloat();

}

StockData::StockData(const StockData &other)
    :QObject(0)
{
    mName = other.mName;
    currentPrice = other.currentPrice;
//    lowest = 0.0f;
//    highest = 500.0f;
}

QString StockData::name() const
{
    return mName;
}

void StockData::setName(const QString &value)
{
    mName = value;
}

float StockData::getCurrentPrice() const
{
    return currentPrice;
}

void StockData::setCurrentPrice(float value)
{
    currentPrice = value;
}

float StockData::getHighest() const
{
    return dayHigh;
}

void StockData::setHighest(float value)
{
    dayHigh = value;
}

float StockData::getLowest() const
{
    return dayLow;
}

float  StockData::getPriceChange() const
{
    return change;
}

QString StockData::currency() const
{
    return mCurrency;
}

float StockData::getTwoHundredDayAverage() const
{
    return twoHundredDayAverage;
}

float StockData::getFiftyDayAverage() const
{
    return fiftyDayAverage;
}

void StockData::setHistoricalData(const QJsonArray &data)
{
    mHistoricalData.setData(data);
}

//const QVariant &StockData::operator[](std::size_t idx) const
//{
//    return getValueByIndex(idx);
//}

//QVariant &StockData::operator[](std::size_t idx)
//{
//    return const_cast<QVariant&>(getValueByIndex(idx));
//}

const QVariant StockData::getValueByIndex(std::size_t idx) const
{
    switch(idx)
    {
    case 0:
        return QVariant::fromValue(mName);
        break;
    case 1:
        return QVariant::fromValue(mSymbol);
        break;
    case 2:
        return QVariant::fromValue(currentPrice);
        break;
    case 3:
        return QVariant::fromValue(dayHigh);
        break;
    case 4:
        return QVariant::fromValue(dayLow);
        break;
    case 5:
        return QVariant::fromValue(change);
        break;
    case 6:
        return QVariant::fromValue(twoHundredDayAverage);
        break;
    case 7:
        return QVariant::fromValue(fiftyDayAverage);
        break;
    case 8:
        return QVariant::fromValue(mCurrency);
        break;
    default:
        return QVariant();
    }
}

QJsonArray StockData::getLabels(int size) const
{
    return mHistoricalData.getLabels(size);
}


QJsonArray StockData::getValues(int size) const
{
    return mHistoricalData.getValues(size);

}

void StockData::setLowest(float value)
{
    dayLow = value;
}

void StockData::setChange(float pChange)
{
    change = pChange;
}

QString StockData::symbol() const
{
    return mSymbol;
}


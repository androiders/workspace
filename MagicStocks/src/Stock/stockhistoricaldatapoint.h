#ifndef STOCKHISTORICALDATAPOINT_H
#define STOCKHISTORICALDATAPOINT_H

#include <QObject>

class StockHistoricalDataPoint : public QObject
{
    Q_OBJECT
public:
    explicit StockHistoricalDataPoint(QObject *parent = 0);

signals:

public slots:

private:

    QString mSymbol;

    //QDate mDate;

    float mOpenPrice;

    float mClosePrice;

    float mDayHigh;

    float mDayLow;

    int mVolume;
};

#endif // STOCKHISTORICALDATAPOINT_H

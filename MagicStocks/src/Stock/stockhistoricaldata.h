#ifndef STOCKHISTORICALDATA_H
#define STOCKHISTORICALDATA_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

class StockHistoricalData : public QObject
{
    Q_OBJECT
public:
    StockHistoricalData(QObject * parent = 0)
        :QObject(parent){}

    explicit StockHistoricalData(const QJsonArray & data, QObject *parent = 0);

    void setData(const QJsonArray & data);

//    StockHistoricalData & operator==(StockHistoricalData && rhs);
//    StockHistoricalData & operator==(StockHistoricalData &rhs);


signals:

public slots:

    int getSize() const;

    QJsonObject getData(int index) const;

    /**
     * @brief getLabels returns a list of labels constructed from the dates for each data point
     * @param nrOfLabels the nr of datapoints to return from the latest and backwards
     * @return an json array of strings of dates
     */
    QJsonArray getLabels(int nrOfLabels = 0) const;

    /**
     * @brief getValues returns the nr of datapoints from the latest and backwards
     * @param nrOfObjects the nr of datapoints  to return
     * @return a json array of data
     */
    QJsonArray getValues(int nrOfObjects = 0) const;

    float getClosingPrice(int index) const;

    QString getDateString(int index) const;

private:

    void calculateAndAddSMA(const QString &key, int sma);

    QVector<QJsonObject> mDataPoints;
};

#endif // STOCKHISTORICALDATA_H

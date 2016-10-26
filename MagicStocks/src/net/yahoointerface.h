#ifndef YAHOOINTERFACE_H
#define YAHOOINTERFACE_H

#include <QObject>
#include "restclient.h"
#include <QJsonArray>
#include <QDate>

class YahooInterface : public QObject
{
    Q_OBJECT
public:
    explicit YahooInterface(QObject *parent = 0);

//    void getStockByName(const QString & name);

public slots:

    void searchStocks(const QString & searchText, const QString & region = "SE", const QString & lang ="sv-SE");

    void getStockBySymbol(const QString & symbol);

    void getStocksBySymbol(const QStringList & symbols);

    void getHistoricalStockData(const QString & symbol, const QDate from, const QDate to);


signals:

    void noStockFound(QString errorMsg);

    void stocksReady(const QJsonArray & stocks);

    void stockSearchReady(const QVariantList & searchResults);

    void stockHistoricalDataReady(const QString & symbol, const QJsonArray & stockData);


public slots:

     void stockDataReady(const QString & data, unsigned int reqId);

private:

     void parseStockData(const QString & data);

     void parseSearchResult(const QString & data);

     void parseHistoricalStockData(const QString & data);
     //DataPair getSymbolQueryPair(const QStringList & symbols) const;

     DataPair getJsonFormatPair() const;
     DataPair getDiagnosticsPair() const;
     DataPair getEnvPair() const;
     DataPair getCallbackPair(const QString & cb = "") const;

     QString stockTable;
     QString queryCallBack;
     QString historicalTable;

     RestClient rc;

     unsigned int mSearchReqId;

     unsigned int mStockReadyReqId;

     unsigned int mHistoricalDataReqId;
};

#endif // YAHOOINTERFACE_H

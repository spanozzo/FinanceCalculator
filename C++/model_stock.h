#ifndef STOCK_H
#define STOCK_H
#include "model_asset.h"

class Stock: public Asset {
  private:
    double dividendo;                         // valore dividendo
  public:
    Stock(QString, double, double, unsigned int, double);
    double getDividendo() const;
    double gain(unsigned int) const;
    double gainDividendo() const;
    double totalGain() const;
    bool operator==(const Asset*&) const;
    const Asset* unionAsset(const Asset*&) const;
};

#endif // STOCK_H

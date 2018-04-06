#include "model_stock.h"

Stock::Stock(QString n, double p, double sp, unsigned int u, double div =0): Asset(n, p, sp, u), dividendo(div) {
  if(dividendo < 0)
    dividendo = 0;
}

double Stock::getDividendo() const {
  return dividendo;
}

double Stock::gain(unsigned int sellUnit) const {
  if(sellUnit > 0) {
    if(sellUnit > getUnit())
      sellUnit = getUnit();
    double ris = (getSellPrice() - getPrice()) * sellUnit;
    if(getTaxOn() && (ris > 0))
      return (ris - ris * getTassa());
    return ris;
  }
  return 0;
}

double Stock::gainDividendo() const {
  double ris = getUnit() * dividendo;
  if(getTaxOn())
     return (ris - ris * getTassa());
  return ris;
}

double Stock::totalGain() const {
  return (gain(getUnit()) + gainDividendo());
}

bool Stock::operator==(const Asset *&ps) const {
  const Stock* s = dynamic_cast<const Stock*>(ps);
  if(s)
    return (getName() == s->getName() && getPrice()==s->getPrice() && getSellPrice()==s->getSellPrice()
            && dividendo==s->dividendo);
  return false;
}

const Asset* Stock::unionAsset(const Asset*& b) const {
  const Stock *sa = static_cast<const Stock*>(this);
  const Stock *sb = static_cast<const Stock*>(b);
  int newUnit = sa->getUnit() + sb->getUnit();
  double newPrice = (sa->getPrice()*sa->getUnit() + sb->getPrice()*sb->getUnit()) / newUnit;
  double newSellPrice = (sa->getSellPrice()*sa->getUnit() + sb->getSellPrice()*sb->getUnit()) / newUnit;
  double newDividendo = (sa->getDividendo()*sa->getUnit() + sb->getDividendo()*sb->getUnit()) / newUnit;
  return new Stock(sa->getName(), newPrice, newSellPrice, newUnit, newDividendo);
}

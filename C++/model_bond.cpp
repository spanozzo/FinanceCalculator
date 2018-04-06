#include "model_bond.h"

Bond::Bond(QString n, double p, double sp, unsigned int u, double c=0, bool ts=false): Asset(n, p, sp, u), coupon(c), stato(ts) {
  if(coupon < 0)
    coupon = 0;
}

double Bond::tassaStato = 0.125;

double Bond::gain(unsigned int unit) const {
  double ris = (getSellPrice() - getPrice()) * unit;
  if(getTaxOn() && (ris > 0)) {
    if(stato)
      return (ris - ris * tassaStato);
    return (ris - ris * getTassa());
  }
  return ris;
}

double Bond::gainCedola() const {
  double ris = (getInvestimento() * coupon) / 100;
  if(getTaxOn()) {
    if(stato)
      return (ris - ris * tassaStato);
    else
      return (ris - ris * getTassa());
  }
  return ris;
}

double Bond::totalGain() const {
  return (gain(getUnit()) + gainCedola());
}

bool Bond::operator==(const Asset *&pb) const {
  const Bond* b = dynamic_cast<const Bond*>(pb);
  if(b)
    return (getName()==b->getName() && getPrice()==b->getPrice() && getSellPrice()==b->getSellPrice()
            && coupon==b->coupon && stato==b->stato);
  return false;
}

double Bond::getCoupon() const {
  return coupon;
}

bool Bond::getStato() const {
  return stato;
}
const Asset* Bond::unionAsset(const Asset*& b) const {
  const Bond *ba = static_cast<const Bond*>(this);
  const Bond *bb = static_cast<const Bond*>(b);
  int newUnit = ba->getUnit() + bb->getUnit();
  double newPrice = (ba->getPrice()*ba->getUnit() + bb->getPrice()*bb->getUnit()) / newUnit;
  double newSellPrice = (ba->getSellPrice()*ba->getUnit() + bb->getSellPrice()*bb->getUnit()) / newUnit;
  double newCoupon = (ba->getInvestimento()*ba->getCoupon() + bb->getInvestimento()*bb->getCoupon()) / (ba->getInvestimento()+bb->getInvestimento());
  return new Bond(ba->getName(), newPrice, newSellPrice, newUnit, newCoupon, ba->getStato());
}

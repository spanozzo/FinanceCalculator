#include "model_derivative.h"

Derivative::Derivative(QString n, double p, double sp, unsigned int u, unsigned int l =1, bool ss =false): Asset(n, p, sp, u), leva(l), shortSell(ss) {
  if(leva < 1)
    leva = 1;
  else
    if(leva > maxLeva)
      leva = maxLeva;
}

unsigned int Derivative::maxLeva = 400;

double Derivative::totalGain() const {
  return gain(getUnit());
}

double Derivative::gain(unsigned int u) const {
  if(getPrice() != getSellPrice()) {
    double investimento = getPrice() * u;
    double prestito = (investimento * leva) - investimento;
    double ris = (getSellPrice() * u * leva) - (investimento + prestito);
    if(shortSell)
      ris *= -1;
    if(getTaxOn() && (ris > 0))
      return (ris - (ris * getTassa()));
    return ris;
  }
  return 0;
}

bool Derivative::operator==(const Asset *&pd) const {
  const Derivative* d = dynamic_cast<const Derivative*>(pd);
  if(d)
    return (getName() == d->getName() && getPrice()==d->getPrice() && getSellPrice()==d->getSellPrice()
            && leva==d->leva && shortSell==d->shortSell);
  return false;
}

bool Derivative::getShort() const {
  return shortSell;
}

uint Derivative::getLeva() const {
  return leva;
}
const Asset* Derivative::unionAsset(const Asset*& b) const {
  const Derivative *da = static_cast<const Derivative*>(this);
  const Derivative *db = static_cast<const Derivative*>(b);
  int newUnit = da->getUnit() + db->getUnit();
  double newPrice = (da->getPrice()*da->getUnit() + db->getPrice()*db->getUnit()) / newUnit;
  double newSellPrice = (da->getSellPrice()*da->getUnit() + db->getSellPrice()*db->getUnit()) / newUnit;
  return new Derivative(da->getName(), newPrice, newSellPrice, newUnit, da->getLeva(), da->getShort());
}

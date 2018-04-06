#include "model_asset.h"

Asset::Asset(QString n ="", double p =0, double sp =0, unsigned int u =0): name(n), price(p), sellPrice(sp), unit(u) {
  if((price < 0) || (sellPrice < 0)) {
    price = 0;
    sellPrice = 0;
    unit = 0;
    name = "";
  }
  if(unit <= 0) {
    unit = 1;
  }
}
bool Asset::taxOn = false;
double Asset::tassa = 0.26;

double Asset::getPrice() const{
  return price;
}

double Asset::getSellPrice() const {
  return sellPrice;
}

unsigned int Asset::getUnit() const{
  return unit;
}

bool Asset::getTaxOn() {
  return taxOn;
}

double Asset::getTassa() {
  return tassa;
}

QString Asset::getName() const {
  return name;
}

double Asset::diffgain(const Asset* &a) const {
  return (((a->roi() - roi()) / roi()) * 100);
}

double Asset::operator+(const Asset& a) const {
  return (totalGain() + a.totalGain());
}

double operator+(double asset1, const Asset& asset2) {
  return (asset1 + asset2.totalGain());
}

double Asset::getInvestimento() const {
  return (price * unit);
}

double Asset::roi() const {
  return ((totalGain() / getInvestimento()) * 100);
}

void Asset::setTaxOn(bool t) {
  if(taxOn != t)
    taxOn = t;
}

#include "model_portfolio.h"
#include <typeinfo>

Portfolio::~Portfolio() {
  auto it = assets.begin();
  for(; it != assets.end(); ++it){
    delete *it;
    it = assets.erase(it);
    it--;
  }
}

double Portfolio::valoreTot() const {
  auto cit = assets.begin();
  double ris = 0.0;
  for(; cit != assets.end() ; ++cit)
    ris += (*cit)->getInvestimento();
  return ris;
}

double Portfolio::gainTot() const {
  auto cit = assets.begin();
  double ris = 0.0;
  for(; cit != assets.end() ; ++cit)
    ris += (*cit)->totalGain();
  return ris;
}

void Portfolio::addAsset(const Asset *a) {
  assets.push_back(a);
}

unsigned int Portfolio::getSize() const {
  return assets.size();
}

const Asset* Portfolio::getAsset_n(int n) const {
  return assets[n];
}

void Portfolio::removeAsset(int n) {
  delete assets[n];
  assets.remove(n);
}

void Portfolio::setTax(bool b) {
  Asset::setTaxOn(b);
}

int Portfolio::addUnionAsset(int n, int k) {
  bool comp = true;
  const Asset *a = assets[n];
  const Asset *b = assets[k];
  if(typeid(*a) == typeid(*b)) {
    if(dynamic_cast<const Stock*>(a))
      addAsset(a->unionAsset(b));
    else {
      const Bond *ba = dynamic_cast<const Bond*>(a);
      if(ba) {
        const Bond *bb = static_cast<const Bond*>(b);
        if(ba->getStato() == bb->getStato())
          addAsset(a->unionAsset(b));
        else
          comp = false;
      }
      else {
        const Derivative *da = static_cast<const Derivative*>(a);
        const Derivative *db = static_cast<const Derivative*>(b);
        if((da->getShort() == db->getShort()) && (da->getLeva() == db->getLeva()))
          addAsset(a->unionAsset(b));
        else
          comp = false;
      }
    }
    if(comp) {
      if(n<k) {
        removeAsset(k);
        removeAsset(n);
      }
      else {
        removeAsset(n);
        removeAsset(k);
      }
      return assets.size()-1;
    }
  }
  return assets.size()+1;
}

double Portfolio::totalReturn() const {
  return (valoreTot() + gainTot());
}

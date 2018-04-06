#include "controller_portfolio.h"

ControllerPortfolio::ControllerPortfolio(MainWindow *m): pp(new Portfolio()), mw(m) {
  connect(this, SIGNAL(add_tableRow_sig(QString,QString,double,double,uint,double,double,bool,bool,uint)),
          mw, SLOT(add_tableRow_s(QString,QString,double,double,uint,double,double,bool,bool,uint)));
  connect(this, SIGNAL(remove_asset_gui_sig(int)), mw, SLOT(remove_asset_gui(int)));
}
ControllerPortfolio::~ControllerPortfolio(){
  delete pp;
}

void ControllerPortfolio::add_asset_s(QString aType, QString aName, double aPrice, double aSellPrice, uint aUnit,
                                             double aDiv, double aCoup, bool aStateBond, bool aShortSell, uint aLeva) {
  int size = getSize();
  if(aType == "Stock") {
    Stock* s = new Stock(aName, aPrice, aSellPrice, aUnit, aDiv);
    pp->addAsset(s);
  }
  else {
    if(aType == "Bond") {
      Bond* b = new Bond (aName, aPrice, aSellPrice, aUnit, aCoup, aStateBond);
      pp->addAsset(b);
    }
    else {
      Derivative *d = new Derivative(aName, aPrice, aSellPrice, aUnit, aLeva, aShortSell);
      pp->addAsset(d);
    }
  }
  if(getSize() > size)     //ho effettivamente aggiunto l'asset
    emit add_tableRow_sig(aType, aName, aPrice, aSellPrice, aUnit, aDiv, aCoup, aStateBond, aShortSell, aLeva);
}

int ControllerPortfolio::getSize() const {
  return pp->getSize();
}

void ControllerPortfolio::remove_asset_s(int n) {
  pp->removeAsset(n);
  emit remove_asset_gui_sig(n);
}

double ControllerPortfolio::getGain(int n, int u) const {
  const Asset* a = pp->getAsset_n(n);
  if(u<1 || u>a->getUnit())
    return a->gain(a->getUnit());
  return a->gain(u);
}
double ControllerPortfolio::getROI(int n) const {
  const Asset* a = pp->getAsset_n(n);
  return (a->roi());
}
double ControllerPortfolio::getCouponGain(int n) const {
  const Bond* a = static_cast<const Bond*>(pp->getAsset_n(n));
  return (a->gainCedola());
}
double ControllerPortfolio::getDividendGain(int n) const {
  const Stock* a = static_cast<const Stock*>(pp->getAsset_n(n));
  return (a->gainDividendo());
}
double ControllerPortfolio::getTotalGain(int n) const {
  const Asset* a = pp->getAsset_n(n);
  return (a->totalGain());
}
double ControllerPortfolio::getAdd(int n, int k) const {
  const Asset* a = pp->getAsset_n(n);
  const Asset* b = pp->getAsset_n(k);
  return ((*const_cast<Asset*>(a))+(*b));
}
double ControllerPortfolio::getAdd(double pre, int n) const {
  const Asset* a = pp->getAsset_n(n);
  return (pre + (*a));
}

double ControllerPortfolio::getDiffGain(int n, int k) const {
  const Asset* a = pp->getAsset_n(n);
  const Asset* b = pp->getAsset_n(k);
  return ((*const_cast<Asset*>(a)).diffgain(b));
}

void ControllerPortfolio::change_tax_s(bool b) {
  pp->setTax(b);
}

QString ControllerPortfolio::getAssetName(int n) const {
  return pp->getAsset_n(n)->getName();
}

void ControllerPortfolio::union_assets_s(int n, int k) {
  uint i = pp->addUnionAsset(n, k);
  if(i < pp->getSize()) {              // se Portfolio ha effettivamente effettuato l'unione, l'indice i sarà minore della size del Portfolio (return assets.size()-1), altrimenti sarà maggiore (assets.size()+1)
    const Asset* x = pp->getAsset_n(i);
    QString aType;
    QString aName = x->getName();
    double aPrice = x->getPrice();
    double aSellPrice = x->getSellPrice();
    uint aUnit = x->getUnit();
    double aDiv, aCoup;
    bool aStateBond, aShortSell;
    uint aLeva;
    const Stock* sx = dynamic_cast<const Stock*>(x);
    if(sx) {
      aType = "Stock";
      aDiv = sx->getDividendo();
      aCoup = 0;
      aStateBond = 0;
      aShortSell = 0;
      aLeva = 0;
    }
    else {
      const Bond* bx = dynamic_cast<const Bond*>(x);
      if(bx) {
        aType = "Bond";
        aDiv = 0;
        aCoup = bx->getCoupon();
        aStateBond = bx->getStato();
        aShortSell = 0;
        aLeva = 0;
      }
      else {
        const Derivative* dx = static_cast<const Derivative*>(x);
        aType = "Derivative";
        aDiv = 0;
        aCoup = 0;
        aStateBond = 0;
        aShortSell = dx->getShort();
        aLeva = dx->getLeva();
      }
    }
    emit add_tableRow_sig(aType, aName, aPrice, aSellPrice, aUnit, aDiv, aCoup, aStateBond, aShortSell, aLeva);
    if(n<k) {
      emit remove_asset_gui_sig(k);
      emit remove_asset_gui_sig(n);
    }
    else {
      emit remove_asset_gui_sig(n);
      emit remove_asset_gui_sig(k);
    }
  }
}

double ControllerPortfolio::getTotalReturn() const {
  return pp->totalReturn();
}

double ControllerPortfolio::getGainPortfolio() const {
  return pp->gainTot();
}

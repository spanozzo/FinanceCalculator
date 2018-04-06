#ifndef BOND_H
#define BOND_H
#include "model_asset.h"

class Bond: public Asset {
  private:
    double coupon;                                    // valore cedola
    bool stato;                                       // true sse bond di stato
    static double tassaStato;
  public:
    Bond(QString, double, double, unsigned int, double, bool);
    double gain(unsigned int) const;
    double gainCedola() const;
    double totalGain() const;
    bool operator==(const Asset*&) const;
    double getCoupon() const;
    bool getStato() const;
    const Asset* unionAsset(const Asset*&) const;
};

#endif // BOND_H

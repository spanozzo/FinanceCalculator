#ifndef DERIVATIVE_H
#define DERIVATIVE_H
#include "model_asset.h"

class Derivative: public Asset {
  private:
    unsigned int leva;                              // valore leva
    static unsigned int maxLeva;
    bool shortSell;                                 // true sse posizione short
  public:
    Derivative(QString, double, double, unsigned int, unsigned int, bool);
    double totalGain() const;
    double gain(unsigned int) const;
    bool operator==(const Asset*&) const;
    bool getShort() const;
    uint getLeva() const;
    const Asset* unionAsset(const Asset*&) const;
};

#endif // DERIVATIVE_H

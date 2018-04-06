#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include "model_asset.h"
#include "model_stock.h"
#include "model_bond.h"
#include "model_derivative.h"
#include <QVector>

class Portfolio {
  private:
    QVector<const Asset*> assets;
  public:
    ~Portfolio();
    double valoreTot() const;
    double gainTot() const;
    void addAsset(const Asset*);                // aggiunge al portfolio di invocazione l'asset
    void removeAsset(int);                      // rimuove l'asset in (int)-esima posizione
    unsigned int getSize() const;
    const Asset* getAsset_n(int) const;         // ritorna un puntatore costante all'asset (int)-esimo
    void setTax(bool);
    /* aggiunge il nuovo asset dato dall'unione dei due asset in (int)-esima pos. nel vector assets e,
     * se l'unione è andata a buon fine, ritorna la sua posizione, altrimenti ritorna il valore (size + 1) */
    int addUnionAsset(int, int);
    double totalReturn() const;                 // ritorna la somma degli investimenti in portfolio + i gain totali su di essi
};

#endif // PORTFOLIO_H

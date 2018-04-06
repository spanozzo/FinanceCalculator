#ifndef ASSET_H
#define ASSET_H
#include<QString>

class Asset {
  private:
    QString name;                  // nome asset
    double price;                  // prezzo unitario asset
    double sellPrice;              // prezzo di vendita unitario asset
    static bool taxOn;             // se tax == true nel calcolo del rendimento trattengo tasse
    static double tassa;           // tassazione al 26%
    unsigned int unit;             // # unità asset possedute

  protected:
    Asset(QString, double, double, unsigned int);
    static bool getTaxOn();
    static double getTassa();

  public:
    double getPrice() const;
    double getSellPrice() const;
    unsigned int getUnit() const;
    double getInvestimento() const;                             // ritorna il prezzo di acquisto * unità acquistate
    static void setTaxOn(bool);
    QString getName() const;
    virtual double gain(unsigned int) const =0;                 // ritorna il gain/loss dalla vendita dell'asset (chiede il numero di unità vendute)
    virtual double totalGain() const =0;                        // ritorna il gain/loss dalla vendita dell'asset e da eventuali altri guadagni (dividendo o cedola)
    virtual double roi() const;                                 // ritorna il guadagno % di un'investimento
    /* restituisce il gain/loss rispetto ad un altro investimento
     * (es. compro stock A a 1 e vendo a 2, compro stock B a 1 e vendo a 3
     * ->A.gain() = 100, B.gain() = 200 --> A.diffgain(B) = 50 (gain fra il rendimento di A e quello di B))*/
    virtual double diffgain(const Asset* &) const;
    double operator+(const Asset&) const;                       // somma del gain totale di due asset
    virtual bool operator==(const Asset* &) const =0;
    virtual const Asset* unionAsset(const Asset*&) const =0;    // unione
    virtual ~Asset() =default;
};
double operator+(double, const Asset&);

#endif //ASSET_H

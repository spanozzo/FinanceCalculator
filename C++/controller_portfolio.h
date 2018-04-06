#ifndef CONTROLLER_PORTFOLIO_H
#define CONTROLLER_PORTFOLIO_H

#include <QObject>
#include <QString>
#include <QRegularExpression>
#include "model_portfolio.h"
#include "view_mainwindow.h"

class MainWindow;

class ControllerPortfolio: public QObject {
  Q_OBJECT

  signals:
    void add_tableRow_sig(QString, QString, double, double, uint, double, double, bool, bool, uint);  // Aggiunge una nuova riga alla tabella con questi valori
    void remove_asset_gui_sig(int);

  private slots:
    void change_tax_s(bool);                          // cambio valore taxOn
    void remove_asset_s(int);                         // rimuove l'asset in posizione (int)-esima
    void add_asset_s(QString, QString, double, double, uint, double, double, bool, bool, uint);   // Aggiunge l'asset con questi valori
    void union_assets_s(int, int);                    // unisce gli asset nelle due posizione (int)-esime

  private:
    Portfolio* pp;
    MainWindow* mw;

  public:
    ControllerPortfolio(MainWindow*);
    ~ControllerPortfolio();
    int getSize() const;
    double getGain(int, int) const;
    double getAdd(int, int) const;                     // ritorna il valore della somma dei gain tot. dei due asset in pos. (int)-esima
    double getAdd(double, int) const;                  // ritorna il valore della somma del precedente risultato con il gain tot. dell'asset in pos. (int)-esima
    double getDividendGain(int) const;
    double getDiffGain(int, int) const;
    double getTotalGain(int) const;
    double getCouponGain(int) const;
    double getROI(int) const;
    QString getAssetName(int) const;
    double getTotalReturn() const;
    double getGainPortfolio() const;
};

#endif // CONTROLLER_PORTFOLIO_H

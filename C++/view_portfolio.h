#ifndef VIEW_PORTFOLIO_H
#define VIEW_PORTFOLIO_H
#include <QWidget>
#include "ui_tabPortfolio.h"
#include "view_mainwindow.h"

namespace Ui {
  class PortfolioTab;
}

class ControllerPortfolio;

class PortfolioTab : public QWidget
{
    Q_OBJECT

  public:
    explicit PortfolioTab(QWidget *parent = 0, ControllerPortfolio* =0);
    ~PortfolioTab();

  private:
    Ui::view_portfolio *ui;
    ControllerPortfolio *cp;
    bool stock_state=true, bond_state=true, derivative_state=true;
    void stockEditState(bool);                            // setta stock_state a bool
    void bondEditState(bool);                             // setta bond_state a bool
    void derivativeEditState(bool);                       // setta derivative_state a bool
    bool checkInput() const;                              // controlla che i campi dati inseriti siano corretti
    int getRow() const;                                   // ritorna la pos. della riga selezionata
    bool checkSelect() const;                             // controlla che almeno una riga della tabella sia selezionata
    QIcon *na;
    QIcon *checked;
    QIcon *notChecked;

  private slots:
    void on_type_comboBox_currentTextChanged(const QString &arg1);          // cambia la visualizzazione degli elementi in base al tipo selezionato
    void on_addButton_clicked();
    void on_resetButton_clicked();
    void on_removeButton_clicked();
    void add_tableRow_portfolio(QString dType, QString dName, double dPrice, double dSellPrice, uint dUnit,     // aggiunge una riga con questi valori nella tabella
                                double dDividend, double dCoupon, bool dState, bool dShort, uint dLeva);
    void remove_tableRow_portfolio(int);                                                                        // rimuove la riga in pos. (int)-esima dalla tabella

  signals:
    void remove_asset_sig(int);                                       // signal verso cp per rimuovere l'asset in pos (int)-esima dal portfolio e dalle tabelle
    void add_asset_sig(QString, QString, double, double, uint,        // signal verso cp per aggiungere l'asset nel portfolio e nelle tabelle
                       double, double, bool, bool, uint);
};

#endif // VIEW_PORTFOLIO_H

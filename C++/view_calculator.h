#ifndef VIEW_CALCULATOR_H
#define VIEW_CALCULATOR_H
#include <QWidget>
#include "ui_tabCalculator.h"
#include "view_mainwindow.h"

namespace Ui {
  class CalculatorTab;
}

class ControllerPortfolio;

class CalculatorTab : public QWidget {
    Q_OBJECT

  public:
    explicit CalculatorTab(QWidget *parent = 0, ControllerPortfolio* =0);
    ~CalculatorTab();

  private:
    Ui::view_calculator *ui;
    ControllerPortfolio *cp;
    bool preAdd=false;                        // true sse l'operazione precedente era una +
    int getRow() const;                       // ritorna la pos. della riga selezionata
    bool checkSelect() const;                 // controlla che almeno una riga della tabella sia selezionata
    QIcon *na;
    QIcon *checked;
    QIcon *notChecked;

  private slots:
    void on_gain_pushButton_clicked();
    void on_differenceGain_pushButton_clicked();
    void on_gainDividendo_pushButton_clicked();
    void on_totalGain_pushButton_clicked();
    void on_ROI_pushButton_clicked();
    void on_gainCedola_pushButton_clicked();
    void on_add_pushButton_clicked();
    void on_union_pushButton_clicked();
    void on_valTotale_pushButton_clicked();
    void on_pushButton_clicked();
    void change_maxUnit_s(int, int);                                     // cambia il valore dello spinBox Unità in base all'asset selezionato
    void add_tableRow_calculator(QString, QString, double, double, uint, // aggiunge una riga con questi valori nella tabella
                                 double, double, bool, bool, uint);
    void remove_tableRow_calculator(int);                                // rimuove la riga in pos. (int)-esima dalla tabella e setta nuovo max 'Secondo Operando'

  signals:
    void result_sig(double);          // signal verso QLCDNumber
    void union_assets_sig(int, int);  // signal verso cp per unione assets in pos (int)-esima
};

#endif // VIEW_CALCULATOR_H

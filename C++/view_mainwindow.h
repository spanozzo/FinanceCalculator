#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QModelIndexList>
#include "controller_portfolio.h"
#include "view_calculator.h"
#include "view_portfolio.h"
#include "ui_calculator.h"

class ControllerPortfolio;
class CalculatorTab;
class PortfolioTab;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    ControllerPortfolio *cp;
    CalculatorTab *ct;
    PortfolioTab *pt;

  private slots:
    void add_tableRow_s(QString, QString, double, double, uint,   // slot per aggiunta riga tabelle ct e pt
                        double, double, bool, bool, uint);
    void remove_asset_gui(int);                                   // slot per eliminazione riga tabelle ct e pt

  signals:
    void remove_assetnTable_sig(int);                             // signal verso ct e pt per eliminazione riga tabella
    void add_tableRow_sig(QString, QString, double, double, uint, // signal verso ct e pt per aggiunta riga tabella
                          double, double, bool, bool, uint);
};

#endif // MAINWINDOW_H

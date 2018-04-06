#include "view_portfolio.h"
PortfolioTab::PortfolioTab(QWidget *parent, ControllerPortfolio *c): QWidget(parent), ui(new Ui::view_portfolio), cp(c) {
  ui->setupUi(this);

  bondEditState(false);
  derivativeEditState(false);

  ui->portfolio_tableWidget->setColumnCount(10);
  ui->portfolio_tableWidget->setHorizontalHeaderLabels(QStringList() << "Tipo" << "Nome" << "Prezzo" << "Pr.Vendita" << "Unità" << "Dividendo" << "Cedola" << "Bond Gov." << "Short" << "Leva");


  connect(this, SIGNAL(remove_asset_sig(int)), cp, SLOT(remove_asset_s(int)));
  connect(this, SIGNAL(add_asset_sig(QString,QString,double,double,uint,double,double,bool,bool,uint)),
          cp, SLOT(add_asset_s(QString,QString,double,double,uint,double,double,bool,bool,uint)));

  for(int c=0; c < ui->portfolio_tableWidget->horizontalHeader()->count(); ++c)
    ui->portfolio_tableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
  na = new QIcon(":/icon/icone/not_available.png");
  checked = new QIcon(":/icon/icone/checked.png");
  notChecked = new QIcon(":/icon/icone/notChecked.png");
}
PortfolioTab::~PortfolioTab() {
  delete ui;
  delete na;
  delete checked;
  delete notChecked;
}

void PortfolioTab::stockEditState(bool b) {
  if(stock_state != b) {
    stock_state = b;
    if(stock_state == false)
      ui->dividend_doubleSpinBox->setDisabled(1);
    else
      ui->dividend_doubleSpinBox->setEnabled(1);
  }
}
void PortfolioTab::bondEditState(bool b) {
  if(bond_state != b) {
    bond_state = b;
    if(bond_state == false) {
      ui->bond_checkBox->setDisabled(1);
      ui->coupon_doubleSpinBox->setDisabled(1);
    }
    else {
      ui->bond_checkBox->setEnabled(1);
      ui->coupon_doubleSpinBox->setEnabled(1);
    }
  }
}
void PortfolioTab::derivativeEditState(bool b) {
  if(derivative_state != b) {
    derivative_state = b;
    if(derivative_state == false) {
      ui->derivative_checkBox->setDisabled(1);
      ui->leva_spinBox->setDisabled(1);
    }
    else {
      ui->derivative_checkBox->setEnabled(1);
      ui->leva_spinBox->setEnabled(1);
    }
  }
}
void PortfolioTab::on_type_comboBox_currentTextChanged(const QString &arg1) {
  if(arg1 == "Stock") {
    stockEditState(true);
    bondEditState(false);
    derivativeEditState(false);
  }
  else {
    if(arg1 == "Bond") {
        bondEditState(true);
        stockEditState(false);
        derivativeEditState(false);
    }
    else
      if(arg1 == "Derivative") {
          derivativeEditState(true);
          stockEditState(false);
          bondEditState(false);
      }
  }
}
void PortfolioTab::on_addButton_clicked() {
  if(checkInput()) {
    emit add_asset_sig(ui->type_comboBox->currentText(), ui->name_lineEdit->text(), ui->price_doubleSpinBox->value(),
                       ui->sellPrice_doubleSpinBox->value(), ui->unit_spinBox->value(), ui->dividend_doubleSpinBox->value(),
                       ui->coupon_doubleSpinBox->value(), ui->bond_checkBox->checkState(),
                       ui->derivative_checkBox->checkState(), ui->leva_spinBox->value());
    emit on_resetButton_clicked();
  }
}

void PortfolioTab::on_resetButton_clicked() {
  ui->type_comboBox->setCurrentIndex(0);
  ui->name_lineEdit->setText("");
  ui->price_doubleSpinBox->setValue(0);
  ui->sellPrice_doubleSpinBox->setValue(0);
  ui->unit_spinBox->setValue(1);
  ui->dividend_doubleSpinBox->setValue(0);
  ui->coupon_doubleSpinBox->setValue(0);
  ui->leva_spinBox->setValue(1);
  ui->bond_checkBox->setChecked(false);
  ui->derivative_checkBox->setChecked(false);
}

void PortfolioTab::add_tableRow_portfolio(QString dType, QString dName, double dPrice, double dSellPrice, uint dUnit,
                                double dDividend, double dCoupon, bool dState, bool dShort, uint dLeva) {

  ui->portfolio_tableWidget->insertRow(ui->portfolio_tableWidget->rowCount());
  QTableWidgetItem* tType = new QTableWidgetItem(dType);
  QTableWidgetItem* tName = new QTableWidgetItem(dName);
  QTableWidgetItem* tPrice = new QTableWidgetItem(QString::number(dPrice));
  QTableWidgetItem* tSellPrice = new QTableWidgetItem(QString::number(dSellPrice));
  QTableWidgetItem* tUnit = new QTableWidgetItem(QString::number(dUnit));
  QTableWidgetItem* tDividend, * tCoupon, * tStateBond, * tShortSell, * tLeverage;
  if(dType == "Stock") {
    tDividend = new QTableWidgetItem(QString::number(dDividend));
    tCoupon = new QTableWidgetItem(*na, 0);
    tStateBond = new QTableWidgetItem(*na, 0);
    tShortSell = new QTableWidgetItem(*na, 0);
    tLeverage = new QTableWidgetItem(*na, 0);
  }
  else {
    if(dType == "Bond") {
      tDividend = new QTableWidgetItem(*na, 0);
      tCoupon = new QTableWidgetItem(QString::number(dCoupon));
      tShortSell = new QTableWidgetItem(*na, 0);
      tLeverage = new QTableWidgetItem(*na, 0);
      if(dState)
        tStateBond = new QTableWidgetItem(*checked, 0);
      else
        tStateBond = new QTableWidgetItem(*notChecked, 0);
    }
    else {
      tDividend = new QTableWidgetItem(*na, 0);
      tCoupon = new QTableWidgetItem(*na, 0);
      tStateBond = new QTableWidgetItem(*na, 0);
      tLeverage = new QTableWidgetItem(QString::number(dLeva));
      if(dShort)
        tShortSell = new QTableWidgetItem(*checked, 0);
      else
        tShortSell = new QTableWidgetItem(*notChecked, 0);
    }
  }
  int n = ui->portfolio_tableWidget->rowCount();
  ui->portfolio_tableWidget->setItem(n-1, 0, tType);
  ui->portfolio_tableWidget->setItem(n-1, 1, tName);
  ui->portfolio_tableWidget->setItem(n-1, 2, tPrice);
  ui->portfolio_tableWidget->setItem(n-1, 3, tSellPrice);
  ui->portfolio_tableWidget->setItem(n-1, 4, tUnit);
  ui->portfolio_tableWidget->setItem(n-1, 5, tDividend);
  ui->portfolio_tableWidget->setItem(n-1, 6, tCoupon);
  ui->portfolio_tableWidget->setItem(n-1, 7, tStateBond);
  ui->portfolio_tableWidget->setItem(n-1, 8, tShortSell);
  ui->portfolio_tableWidget->setItem(n-1, 9, tLeverage);
  for(int i=0; i< ui->portfolio_tableWidget->columnCount() ; ++i)
    ui->portfolio_tableWidget->item(n-1, i)->setFlags(ui->portfolio_tableWidget->item(n-1, i)->flags() & ~Qt::ItemIsEditable);
}
void PortfolioTab::remove_tableRow_portfolio(int n) {
  ui->portfolio_tableWidget->removeRow(n);
}

bool PortfolioTab::checkInput() const {
  QMessageBox* msg = new QMessageBox();
  msg->setWindowTitle("Messaggio");
  QRegExp name("[A-Za-z0-9]{1,7}");
  if(!name.exactMatch(ui->name_lineEdit->text())) {
    msg->setText("Nome non valido.\nSono ammessi solo caratteri e numeri (max 7)");
    msg->show();
    return false;
  }
  if((ui->price_doubleSpinBox->value() == 0) || (ui->sellPrice_doubleSpinBox->value() == 0)) {
      msg->setText("Valore prezzo o prezzo di vendita errato.\nSono ammessi solo valori > 0.0");
      msg->show();
      return false;
  }
  if((ui->type_comboBox->currentText() == "Bond") && (ui->coupon_doubleSpinBox->value() == 0)) {
    msg->setText("Valore cedola errato.\nSono ammessi solo valori > 0.0");
    msg->show();
    return false;
  }
  return true;
}
int PortfolioTab::getRow() const {
  QModelIndexList selectedRow = ui->portfolio_tableWidget->selectionModel()->selectedRows();
  return (selectedRow.first().row());
}
bool PortfolioTab::checkSelect() const {
  if(ui->portfolio_tableWidget->selectionModel()->selectedRows().count() == 0) {
    QMessageBox *msg = new QMessageBox();
    msg->setWindowTitle("Attenzione!");
    msg->setText("Nessuna riga selezionata!");
    msg->show();
    return false;
  }
  return true;
}


void PortfolioTab::on_removeButton_clicked() {
  if(checkSelect()) {
    int n = getRow();
    emit remove_asset_sig(n);
  }
}

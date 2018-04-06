#-------------------------------------------------
#
# Project created by QtCreator 2018-01-23T11:47:57
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinanceCalculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    controller_portfolio.cpp \
    model_asset.cpp \
    model_bond.cpp \
    model_derivative.cpp \
    model_portfolio.cpp \
    model_stock.cpp \
    view_mainwindow.cpp \
    view_calculator.cpp \
    view_portfolio.cpp

HEADERS += \
    controller_portfolio.h \
    model_asset.h \
    model_bond.h \
    model_derivative.h \
    model_portfolio.h \
    model_stock.h \
    view_mainwindow.h \
    view_calculator.h \
    view_portfolio.h

FORMS += \
    tabCalculator.ui \
    tabPortfolio.ui \
    calculator.ui

RESOURCES += \
    icon.qrc

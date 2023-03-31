#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("MKPJ - Qt edition"));

    ui->statusbar->showMessage(tr("MKPJ Qt - 0.1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


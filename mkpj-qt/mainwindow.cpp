#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(new QStringListModel(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("MKPJ - Qt edition"));
    ui->statusbar->showMessage(tr("MKPJ Qt - 0.1"));

    // Users should not be able to directly edit the list
    ui->projectListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Testing makefile creation
    Makefile mk;
    mk.addLib("-lcurses");
    mk.addFlag("-ggdb3");;
    mk.setSrcDir("sources");

    // Testing makefile output
    //QFile file("mklog.txt");
    //file.open(QIODevice::WriteOnly | QIODevice::Text);
    //QTextStream out(&file);
    //out << mk.generate();

    Project p(QString("pr"), QDir("."), mk);
    //qDebug() << p;
    p.outputMakefile("debugMakefile.txt");

    projects.append(p);

    // Fills the list view
    QStringList list;
    for (Project &p : projects)
        list << p.getName();
    model->setStringList(list);
    ui->projectListView->setModel(model);

    // Labels should be updated on list selection
    connect(ui->projectListView, SIGNAL(clicked(QModelIndex)), this, SLOT(setProjectInfosLabel()));
}

void MainWindow::setProjectInfosLabel() {
    ui->nameLabelFill->setText(projects.at(ui->projectListView->currentIndex().row()).getName());
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}


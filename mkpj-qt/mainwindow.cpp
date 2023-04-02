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
    ui->statusbar->showMessage(tr("MKPJ Qt - 0.1"));

    // Users should not be able to directly edit the list
    ui->projectListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Testing makefile creation
    //Makefile mk;
    //mk.addLib("-lcurses");
    //mk.addFlag("-ggdb3");;
    //mk.setSrcDir("sources");

    // Testing makefile parsing
    Makefile mk = Makefile::parseMakefile("debugMakefile.txt");
    //mk.addLdFlag("--no-pie");
    mk.addFlag("-Wall");
    mk.addLib("-lcurses");
    mk.setCompiler("clang++");
    qDebug() << mk.generate();

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
    const Project &selected = projects.at(ui->projectListView->currentIndex().row());

    // Project groupBox
    ui->nameLabelFill->setText(selected.getName());


    // Build groupBox
    const Makefile &makefile = selected.getMakefile();
    ui->targetLabelFill->setText(makefile.getTarget());

    QString flags;
    if (!selected.getMakefile().getFlags().empty())
        for (QString &flag : makefile.getFlags())
            flags.append(flag + " ");

    ui->flagsLabelFill->setText(flags);

    QString libs;
    if (!selected.getMakefile().getLibs().empty())
        for (QString &flag : makefile.getFlags())
            flags.append(flag + " ");

    ui->libsLabelFill->setText(libs);

    // Change status bar to match project infos
    ui->statusbar->showMessage(QString(selected.getDirectory().canonicalPath()));
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}


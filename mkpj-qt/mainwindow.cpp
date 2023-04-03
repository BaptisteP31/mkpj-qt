#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editmakefiledialog.h"
#include "ui_editmakefiledialog.h"

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
    mk.setCompiler("g++");
    //qDebug() << mk.generate();

    // Testing makefile output
    //QFile file("mklog.txt");
    //file.open(QIODevice::WriteOnly | QIODevice::Text);
    //QTextStream out(&file);
    //out << mk.generate();

    Project p(QString("Project 1"), QDir("."), mk);
    Project p2(QString("Project 2"), QDir("."), mk);
    //qDebug() << p;
    p.outputMakefile("debugMakefile.txt");

    projects.append(p);
    projects.append(p2);

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
    ui->descLabelFill->setText(selected.getDesc());
    ui->versionLabelFill->setText(selected.getVersion());
    ui->licenceLabelFill->setText(selected.getLicense());


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

void MainWindow::on_editMakefileButton_clicked()
{
    if (ui->projectListView->selectionModel()->selectedIndexes().isEmpty())
    {
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("No project selected");
        messageBox.setText("You cannot edit a Makefile without selecting a project first.");
        messageBox.setStyleSheet("QMessageBox { background-color: #1e1e1e; color: white; }");
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.exec();
        return;
    }

    editMakefileDialog *diag = new editMakefileDialog(this);
    const Project &selected = projects.at(ui->projectListView->currentIndex().row());
    const Makefile &makefile = selected.getMakefile();
    diag->ui->compilerLineEdit->setText(makefile.getCompiler());

    QString flags;
    for (QString &item : makefile.getFlags())
        flags.append(item + " ");

    diag->ui->cflagsLineEdit->setText(flags);

    QString libs;
    for (QString &item : makefile.getLibs())
        libs.append(item + " ");

    diag->ui->ldlibsLineEdit->setText(libs);
    diag->show();
}


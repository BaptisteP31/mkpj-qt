#include "editmakefiledialog.h"
#include "ui_editmakefiledialog.h"

editMakefileDialog::editMakefileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editMakefileDialog)
{
    ui->setupUi(this);
}

editMakefileDialog::~editMakefileDialog()
{
    delete ui;
}

void editMakefileDialog::on_buttonBox_accepted()
{

}


#ifndef EDITMAKEFILEDIALOG_H
#define EDITMAKEFILEDIALOG_H

#include <QDialog>

namespace Ui {
class editMakefileDialog;
}

class editMakefileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editMakefileDialog(QWidget *parent = nullptr);
    ~editMakefileDialog();
    Ui::editMakefileDialog *ui;

private slots:
    void on_buttonBox_accepted();

};

#endif // EDITMAKEFILEDIALOG_H

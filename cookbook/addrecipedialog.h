#ifndef ADDRECIPEDIALOG_H
#define ADDRECIPEDIALOG_H

#include <QDialog>

namespace Ui {
class AddRecipeDialog;
}

class AddRecipeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipeDialog(QWidget *parent = 0);
    ~AddRecipeDialog();

private:
    Ui::AddRecipeDialog *ui;
};

#endif // ADDRECIPEDIALOG_H

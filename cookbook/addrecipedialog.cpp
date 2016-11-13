#include "addrecipedialog.h"
#include "ui_addrecipedialog.h"

AddRecipeDialog::AddRecipeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipeDialog)
{
    ui->setupUi(this);
}

AddRecipeDialog::~AddRecipeDialog()
{
    delete ui;
}

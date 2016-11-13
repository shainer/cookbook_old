#include "viewrecipedialog.h"
#include "ui_viewrecipedialog.h"

ViewRecipeDialog::ViewRecipeDialog(const Recipe& recipe, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewRecipeDialog)
{
    ui->setupUi(this);

    ui->nameLabel->setText( recipe.name() );
    m_tagsModel.setStringList( recipe.tags() );

    ui->tagListView->setModel( &m_tagsModel );
    ui->textEdit->setText( recipe.procedure() );
}

ViewRecipeDialog::~ViewRecipeDialog()
{
    delete ui;
}

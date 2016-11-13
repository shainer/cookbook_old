#include "addrecipedialog.h"
#include "ui_addrecipedialog.h"

AddRecipeDialog::AddRecipeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipeDialog)
{
    ui->setupUi(this);

    connect( ui->nameLineEdit, &QLineEdit::textChanged, this, &AddRecipeDialog::recipeNameChanged );
    connect( ui->nameLineEdit, &QLineEdit::textChanged, this, &AddRecipeDialog::checkValidity );

    connect( ui->textEdit, &QTextEdit::textChanged, this, &AddRecipeDialog::recipeChanged );
    connect( ui->textEdit, &QTextEdit::textChanged, this, &AddRecipeDialog::checkValidity );

    connect( ui->tagLineEdit, &QLineEdit::textChanged, this, &AddRecipeDialog::checkAddButton );
    connect( ui->addTagButton, &QPushButton::clicked, this, &AddRecipeDialog::tagAdded );

    ui->tagListView->setModel(&m_tagsModel);
}

AddRecipeDialog::~AddRecipeDialog()
{
    delete ui;
}

void AddRecipeDialog::recipeNameChanged() {
    m_name = ui->nameLineEdit->text();
}

void AddRecipeDialog::recipeChanged() {
    m_procedure = ui->textEdit->toPlainText();
}

void AddRecipeDialog::checkAddButton() {
    ui->addTagButton->setEnabled( !ui->tagLineEdit->text().isEmpty() );
}

void AddRecipeDialog::tagAdded() {
    QStringList currentTags = m_tagsModel.stringList();
    currentTags << ui->tagLineEdit->text();

    m_tagsModel.setStringList(currentTags);
}

void AddRecipeDialog::checkValidity() {
    // TODO: disable OK button if name or procedure are empty.
}

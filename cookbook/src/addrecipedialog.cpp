#include "addrecipedialog.h"
#include "ui_addrecipedialog.h"

AddRecipeDialog::AddRecipeDialog(TagsModel* currentTagsModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipeDialog),
    m_currentTagsModel(currentTagsModel)
{
    ui->setupUi(this);

    connect( ui->nameLineEdit, &QLineEdit::textChanged, this, &AddRecipeDialog::recipeNameChanged );
    connect( ui->nameLineEdit, &QLineEdit::textChanged, this, &AddRecipeDialog::checkValidity );

    connect( ui->textEdit, &QTextEdit::textChanged, this, &AddRecipeDialog::recipeChanged );
    connect( ui->textEdit, &QTextEdit::textChanged, this, &AddRecipeDialog::checkValidity );

    connect( ui->tagsComboBox, &QComboBox::editTextChanged, this, &AddRecipeDialog::checkAddButton );
    connect( ui->tagsComboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated), this, &AddRecipeDialog::tagSelected );
    connect( ui->addTagButton, &QPushButton::clicked, this, &AddRecipeDialog::tagAdded );

    ui->tagListView->setModel(&m_thisRecipeTagsModel);
    ui->tagsComboBox->setModel(m_currentTagsModel);
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
    ui->addTagButton->setEnabled( !ui->tagsComboBox->currentText().isEmpty() );
}

void AddRecipeDialog::tagSelected(const QString& tag) {
    QStringList currentTags = m_thisRecipeTagsModel.stringList();
    currentTags << tag;
    m_thisRecipeTagsModel.setStringList( currentTags );

    m_currentTagsModel->addTag( tag );
}

void AddRecipeDialog::tagAdded() {
    QStringList currentTags = m_thisRecipeTagsModel.stringList();
    currentTags << ui->tagsComboBox->currentText();
    m_thisRecipeTagsModel.setStringList( currentTags );

    m_currentTagsModel->addTag( ui->tagsComboBox->currentText() );
}

void AddRecipeDialog::checkValidity() {
    // TODO: disable OK button if name or procedure are empty.
}

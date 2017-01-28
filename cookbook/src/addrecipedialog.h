#ifndef ADDRECIPEDIALOG_H
#define ADDRECIPEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QStringListModel>

#include "tags.h"

namespace Ui {
class AddRecipeDialog;
}

class AddRecipeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipeDialog(TagsModel* currentTagsModel, QWidget *parent = 0);
    ~AddRecipeDialog();

    QString name() const { return m_name; }
    QString procedure() const { return m_procedure; }
    QStringList tags() const { return m_thisRecipeTagsModel.stringList(); }

protected slots:
    void recipeNameChanged();
    void recipeChanged();
    void checkValidity();
    void tagAdded();
    void tagSelected(const QString &);
    void checkAddButton();

private:
    Ui::AddRecipeDialog *ui;

    QStringListModel m_thisRecipeTagsModel;
    TagsModel* m_currentTagsModel;

    QString m_name;
    QString m_procedure;
};

#endif // ADDRECIPEDIALOG_H

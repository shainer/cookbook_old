#ifndef VIEWRECIPEDIALOG_H
#define VIEWRECIPEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QStringListModel>

#include "recipe.h"

namespace Ui {
class ViewRecipeDialog;
}

class ViewRecipeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecipeDialog(const Recipe& recipe, QWidget *parent = 0);
    ~ViewRecipeDialog();

private:
    Ui::ViewRecipeDialog *ui;

    QStringListModel m_tagsModel;
};

#endif // VIEWRECIPEDIALOG_H

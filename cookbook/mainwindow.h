#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QList>
#include <QMainWindow>

#include "recipe.h"

namespace Ui {
class MainWindow;
}

class RecipeModel : public QAbstractTableModel {
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex & /*index*/) const Q_DECL_OVERRIDE;

    void addRecipe(Recipe* recipe);
    Recipe *getRecipe(const QModelIndex& index);

private:
    // TODO: load initial list from database at startup.
    QList<Recipe *> m_recipes;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RecipeModel m_recipeModel;

protected slots:
    void addRecipe();
    void viewRecipe(const QModelIndex &);
};

#endif // MAINWINDOW_H

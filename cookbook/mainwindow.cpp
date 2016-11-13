#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addrecipedialog.h"

#include <QDebug>
#include <QPointer>

int RecipeModel::rowCount(const QModelIndex &parent) const {
    return m_recipes.size();
}

int RecipeModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant RecipeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant header;

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch(section) {
            case 0:
                header = QVariant("Recipe name");
            break;

            case 1:
                header = QVariant("Tags");
            break;
        }
    }

    return header;
}

Qt::ItemFlags RecipeModel::flags(const QModelIndex &) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        Recipe* recipe = m_recipes.at( index.row() );
        qDebug() << "Requested recipe" << recipe->name();
        QVariant data;

        switch (index.column()) {
            case 0:
                data = recipe->name();
            break;

            case 1:
                data = recipe->tags();
            break;
        }

        return data;
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
}

void RecipeModel::addRecipe(Recipe *recipe) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_recipes.append(recipe);
    endInsertRows();
}


/** MAIN WINDOW **/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->addRecipeButton, &QPushButton::clicked, this, &MainWindow::addRecipe );

    ui->recipeView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->recipeView->setModel(&m_recipeModel);
    ui->recipeView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRecipe() {
    QPointer<AddRecipeDialog> dlg = new AddRecipeDialog(this);

    if (dlg->exec() == QDialog::Accepted) {
        Recipe* recipe = new Recipe(dlg->name(), dlg->procedure(), dlg->tags());
        m_recipeModel.addRecipe(recipe);
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addrecipedialog.h"
#include "viewrecipedialog.h"

#include <QDebug>
#include <QErrorMessage>
#include <QPointer>

using ::cookbook::storage::RecipeDatabaseStorage;

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

void RecipeModel::deleteRecipe(int index) {
    if (index < 0 || index >= m_recipes.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, 0);
    m_recipes.removeAt(index);
    endRemoveRows();
}

Recipe* RecipeModel::getRecipe(const QModelIndex &index) {
    return m_recipes.at( index.row() );
}


/** MAIN WINDOW **/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    // TODO: proper configuration and installation of files
    m_recipeDb(new RecipeDatabaseStorage("/usr/local/cookbook/recipes.db"))
{
    for (Recipe* recipe : m_recipeDb->loadRecipes()) {
         m_recipeModel.addRecipe(recipe);
    }

    ui->setupUi(this);

    connect( ui->addRecipeButton, &QPushButton::clicked, this, &MainWindow::addRecipe );
    connect( ui->deleteRecipeButton, &QPushButton::clicked, this, &MainWindow::deleteRecipe );

    connect( ui->recipeView, &QAbstractItemView::doubleClicked, this, &MainWindow::viewRecipe );
    ui->recipeView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->recipeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->recipeView->setModel(&m_recipeModel);
    ui->recipeView->show();
}

MainWindow::~MainWindow()
{
    delete m_recipeDb;
    delete ui;
}

void MainWindow::addRecipe() {
    QPointer<AddRecipeDialog> dlg = new AddRecipeDialog(this);

    if (dlg->exec() == QDialog::Accepted) {
        Recipe* recipe = new Recipe(dlg->name(), dlg->procedure(), dlg->tags());

        bool success = m_recipeDb->addRecipe(*recipe);
        int id =  m_recipeDb->generateRecipeId(*recipe);

        if (!success || id == -1) {
            QErrorMessage error_message;
            error_message.showMessage("Error storing the new recipe on the database.");
            return;
        }

        recipe->set_id( id );
        m_recipeModel.addRecipe(recipe);
    }
}

void MainWindow::viewRecipe(const QModelIndex& index) {
    if (index.row() >= m_recipeModel.rowCount()) {
        return;
    }

    Recipe* recipe = m_recipeModel.getRecipe(index);
    QPointer<ViewRecipeDialog> dlg = new ViewRecipeDialog(*recipe, this);
    dlg->exec();
}

void MainWindow::deleteRecipe() {
    QItemSelectionModel* selectionModel = ui->recipeView->selectionModel();

    if (!selectionModel->hasSelection()) {
        return;
    }

    QModelIndex selectionIndex = selectionModel->currentIndex();
    if (!selectionIndex.isValid()) {
        return;
    }

    Recipe* recipe = m_recipeModel.getRecipe(selectionIndex);

    if (m_recipeDb->removeRecipe(*recipe)) {
        m_recipeModel.deleteRecipe(selectionIndex.row());
        delete recipe;
    } else {
        QErrorMessage error_message;
        error_message.showMessage("Error deleting recipe from the database.");
        error_message.exec();
    }
}

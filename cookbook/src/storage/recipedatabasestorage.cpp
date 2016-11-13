#include "recipedatabasestorage.h"
#include <sqlite3.h>

#include <QDebug>

namespace cookbook {
namespace storage {


RecipeDatabaseStorage::RecipeDatabaseStorage(const QString& dbPath) {
    std::string tmp = dbPath.toStdString();
    sqlite3_open(tmp.c_str(), &m_db);
}

RecipeDatabaseStorage::~RecipeDatabaseStorage() {
    sqlite3_close(m_db);
}

QString RecipeDatabaseStorage::lastError() {
    return QString::fromLatin1( sqlite3_errmsg(m_db) );
}

bool RecipeDatabaseStorage::addRecipe(const Recipe &recipe) {
    QString recipeQuery = QString(kInsertRecipeQuery).arg(
                recipe.name()).arg("placeholder").arg( recipe.procedure() );
    qDebug() << recipeQuery;

    std::string tmp = recipeQuery.toStdString();
    int* recipe_id;

    int err = sqlite3_exec(m_db, tmp.c_str(), nullptr, nullptr, nullptr);
    qDebug() << "Error was " << err;
    if (err != 0 ) {
        qDebug() << sqlite3_errmsg(m_db);
        return false;
    }

//    if (!addTags(recipe_id, recipe.tags())) {
//        return false;
//    }

    return true;
}

bool RecipeDatabaseStorage::removeRecipe(const Recipe &recipe) {
    return false;  // to be implemented
}

QList<Recipe> RecipeDatabaseStorage::loadRecipes() {
    return QList<Recipe>();  // to be implemented
}

int RecipeDatabaseStorage::generateRecipeId(const Recipe &recipe) {
    QString query = QString(kGetRecipeId).arg(recipe.name());
    std::string tmp = query.toStdString();
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(m_db, tmp.c_str(), tmp.size(), &statement, nullptr) != 0) {
        return -1;
    }

    if (sqlite3_step(statement) != SQLITE_ROW) {
        return -1;
    }

    int recipe_id = sqlite3_column_int(statement, 0);
    sqlite3_finalize(statement);
    return recipe_id;
}

}
}

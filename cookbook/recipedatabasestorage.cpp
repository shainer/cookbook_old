#include "recipedatabasestorage.h"
#include <sqlite3.h>

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
                recipe.name(), recipe.lastUpdated().toString(), recipe.procedure() );

    std::string tmp = recipeQuery.toStdString();

    int err = sqlite3_exec(m_db, tmp.c_str(), nullptr, nullptr, nullptr);
    if (err != 0 ) {
        return false;
    }

    // TODO: add tags and ingredients.

    return true;
}

bool RecipeDatabaseStorage::removeRecipe(const Recipe &recipe) {
    return false;  // to be implemented
}

QList<Recipe> RecipeDatabaseStorage::loadRecipes() {
    return QList<Recipe>();  // to be implemented
}

}
}

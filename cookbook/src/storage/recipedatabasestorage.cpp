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
    QString deleteQuery = QString(kDeleteRecipe).arg(recipe.id());

    std::string tmp = deleteQuery.toStdString();
    int err = sqlite3_exec(m_db, tmp.c_str(), nullptr, nullptr, nullptr);
    if (err != 0) {
        qDebug() << sqlite3_errmsg(m_db);
        return false;
    }

    // TODO: delete tags and ingredients if unused now?

    return true;
}

QList<Recipe *> RecipeDatabaseStorage::loadRecipes() {
    QString query = QString(kGetAllRecipes);
    std::string tmp = query.toStdString();
    sqlite3_stmt* statement;
    QList<Recipe *> result;

    if (sqlite3_prepare_v2(m_db, tmp.c_str(), tmp.size(), &statement, nullptr) != 0) {
        qDebug() << lastError();
        return result;
    }

    while (sqlite3_step(statement) == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        QString name( (const char *)sqlite3_column_text(statement, 1) );
        QString procedure( (const char *)sqlite3_column_text(statement, 3) );

        result.append( new Recipe(id, name, procedure, QStringList()) );
    }

    sqlite3_finalize(statement);
    // TODO: retrieve tags and ingredients for each recipe.
    return result;
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

#ifndef RECIPEDATABASESTORAGE_H
#define RECIPEDATABASESTORAGE_H

#include "recipe.h"
#include "recipestorage.h"
#include <sqlite3.h>

#include <QString>

namespace cookbook {
namespace storage {

constexpr char kInsertRecipeQuery[] = "INSERT INTO recipes (name, lastupdated, procedure) \
                                     VALUES ($1, $2, $3); ";
constexpr char kInsertTagQuery[] = "INSERT INTO tags (name) VALUES ($0);";
constexpr char kAttachTagQuery[] = "INSERT INTO hasTag (recipe, tag) VALUES ($0, $1)";

class RecipeDatabaseStorage : RecipeStorage
{

public:
    explicit RecipeDatabaseStorage(const QString& dbPath);
    ~RecipeDatabaseStorage() override;

    bool addRecipe(const Recipe& recipe) override;
    bool removeRecipe(const Recipe& recipe) override;
    QList<Recipe> loadRecipes() override;

    QString lastError();

private:
    sqlite3* m_db;
    QString m_lastError;
};

}  // namespace storage
}  // namespace cookbook

#endif // RECIPEDATABASESTORAGE_H

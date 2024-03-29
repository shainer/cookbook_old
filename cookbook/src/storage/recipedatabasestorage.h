#ifndef RECIPEDATABASESTORAGE_H
#define RECIPEDATABASESTORAGE_H

#include "../recipe.h"
#include "recipestorage.h"
#include <sqlite3.h>

#include <QString>

namespace cookbook {
namespace storage {

constexpr char kGetAllRecipes[] = "SELECT id, name, lastupdated, procedure FROM recipes;";
constexpr char kGetAllTags[] = "SELECT name FROM tags;";
constexpr char kGetRecipeTags[] = "SELECT (tag) FROM hasTag WHERE recipe = %0;";
constexpr char kGetRecipeId[] = "SELECT id from recipes WHERE name = \"%0\"";
constexpr char kGetTag[] = "SELECT name FROM tags WHERE name = \"%0\"";

constexpr char kInsertRecipeQuery[] = "INSERT INTO recipes (name, lastupdated, procedure) VALUES (\"%0\", \"%1\", \"%2\"); ";
constexpr char kInsertTagQuery[] = "INSERT INTO tags (name) VALUES (\"%0\");";
constexpr char kAttachTagQuery[] = "INSERT INTO hasTag (recipe, tag) VALUES (%0, \"%1\")";

constexpr char kDeleteRecipe[] = "DELETE FROM recipes WHERE id = %0;";

class RecipeDatabaseStorage : public RecipeStorage
{

public:
    explicit RecipeDatabaseStorage(const QString& dbPath);
    ~RecipeDatabaseStorage() override;

    bool addRecipe(Recipe* recipe) override;
    bool removeRecipe(const Recipe& recipe) override;
    QList<Recipe *> loadRecipes() override;
    QStringList loadTags() override;
    int generateRecipeId(const Recipe &recipe) override;

    QString lastError();

private:
    sqlite3* m_db;
    QString m_lastError;

    QStringList getRecipeTags(int recipe_id);
    bool addTag(int recipe_id, const QString& tag);
    bool tagExists(const QString& tag);
};

}  // namespace storage
}  // namespace cookbook

#endif // RECIPEDATABASESTORAGE_H

#ifndef RECIPESTORAGE_H
#define RECIPESTORAGE_H

#include "recipe.h"
#include <QList>

class RecipeStorage
{

public:
    explicit RecipeStorage() { }
    virtual ~RecipeStorage() { }

    virtual bool addRecipe(const Recipe& recipe) = 0;
    virtual bool removeRecipe(const Recipe& recipe) = 0;
    virtual QList<Recipe> loadRecipes() = 0;
};

#endif // RECIPESTORAGE_H

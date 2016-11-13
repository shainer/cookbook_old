#ifndef RECIPE_H
#define RECIPE_H

#include <QString>
#include <QTime>

struct Ingredient
{
    Ingredient(const QString& name, const QString& unit, int64_t quantity)
        : name(name), unit(unit), quantity(quantity) {}

    QString name;
    QString unit;
    int64_t quantity;
};

class Recipe
{
    typedef QList<Ingredient> IngredientList;

public:
    Recipe(const QString& name, const QString& procedure, const QStringList& tags)
        : m_name(name), m_procedure(procedure), m_tags(tags) {}

    QString name() const { return m_name; }
    QTime lastUpdated() const { return m_lastUpdated; }
    QString procedure() const { return m_procedure; }
    QStringList tags() const { return m_tags; }
    IngredientList ingredients() { return m_ingredients; }

private:

    QString m_name;
    QTime m_lastUpdated;
    QString m_procedure;
    QStringList m_tags;
    IngredientList m_ingredients;
};

#endif // RECIPE_H

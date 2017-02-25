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
        : m_id(-1), m_name(name), m_procedure(procedure), m_tags(tags) {}

    Recipe(int id, const QString& name, const QString& procedure, const QStringList& tags)
        : m_id(id), m_name(name), m_procedure(procedure), m_tags(tags) {}

    int id() const { return m_id; }
    QString name() const { return m_name; }
    // TODO: manage this.
    QTime lastUpdated() const { return m_lastUpdated; }
    QString procedure() const { return m_procedure; }
    QStringList tags() const { return m_tags; }
    // TODO: manage ingredients in the view.
    IngredientList ingredients() { return m_ingredients; }

    void set_id( int id ) { m_id = id; }

private:

    int m_id;
    QString m_name;
    QTime m_lastUpdated;
    QString m_procedure;
    QStringList m_tags;
    IngredientList m_ingredients;
};

#endif // RECIPE_H

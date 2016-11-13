#ifndef RECIPESTORAGE_H
#define RECIPESTORAGE_H

#include <QObject>

class RecipeStorage : public QObject
{
    Q_OBJECT
public:
    explicit RecipeStorage(QObject *parent = 0);

signals:

public slots:
};

#endif // RECIPESTORAGE_H

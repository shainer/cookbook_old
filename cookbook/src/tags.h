#ifndef TAGS_H
#define TAGS_H

#include <QStringListModel>
#include <QSet>

class TagsModel : public QStringListModel {
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    void addTag(const QString& tag);
    void removeTag(const QString& tag);
    bool doesTagExist(const QString& tag) const;

private:
    // TODO: load from database at startup.
    QSet<QString> m_tags;
};

#endif

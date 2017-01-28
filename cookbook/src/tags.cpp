#include "tags.h"

int TagsModel::rowCount(const QModelIndex &parent) const {
    return m_tags.size();
}

QVariant TagsModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return QVariant( m_tags.toList().at( index.row() ) );
    }

    return QVariant();
}

void TagsModel::addTag(const QString& tag) {
    beginInsertRows(QModelIndex(), 0, 0);
    m_tags.insert(tag);
    endInsertRows();
}

void TagsModel::removeTag(const QString &tag) {
    beginRemoveRows(QModelIndex(), 0, 0);
    m_tags.remove(tag);
    endRemoveRows();
}

bool TagsModel::doesTagExist(const QString &tag) const {
    return (m_tags.find(tag) != m_tags.end());
}

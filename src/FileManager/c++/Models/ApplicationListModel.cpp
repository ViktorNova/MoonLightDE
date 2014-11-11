/* 
 * File:   ApplicationListModel.cpp
 * Author: alexis
 * 
 * Created on 4 de noviembre de 2014, 16:10
 */

#include "ApplicationListModel.h"

#include <XdgDesktopFile>

ApplicationListModel::ApplicationListModel(const QString & mimeType) {
    list = XdgDesktopFileCache::getApps(mimeType);
}

ApplicationListModel::~ApplicationListModel() {
}

int ApplicationListModel::rowCount(const QModelIndex & parent) const {
    return list.size();
}

QVariant ApplicationListModel::data(const QModelIndex & index, int role ) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= list.size())
        return QVariant();

    if (role == Qt::DecorationRole)
        return list.at(index.row())->icon();

    if (role == Qt::DisplayRole)
        return list.at(index.row())->name();
    else
        return QVariant();
}
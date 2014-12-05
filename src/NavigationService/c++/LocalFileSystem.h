/*
 * Copyright (C) 2014 Moonlight Desktop Environment Team
 *  Authors:
 *      Alexis López Zubieta <azubieta@uci.cu>
 * 
 * This file is part of Moonlight Desktop Environment.
 *
 * Moonlight Desktop Environment is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight Desktop Environment is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight Desktop Environment. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOCALFILESYSTEM_H
#define	LOCALFILESYSTEM_H

#include "NavigationService/IFileSystemModel.h"

#include <QObject>
#include <QFileSystemModel>

using namespace NavigationService;
/**
 * Decorator class for QFileSystemModel.
 */
class LocalFileSystem : public QObject,  public IFileSystemModel {
    Q_OBJECT
    Q_INTERFACES(NavigationService::IFileSystemModel)
public:
    LocalFileSystem();
    virtual ~LocalFileSystem();

    virtual QAbstractItemModel* effectiveModel();
    
    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;

    virtual QModelIndex index(const QString& path);

    virtual QModelIndex index(const QString& path, const QVariant& data);

    virtual QVariant data(const QModelIndex& index, int role) const;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual QModelIndex parent(const QModelIndex& child) const;

    virtual int rowCount(const QModelIndex& parent) const;

    virtual int columnCount(const QModelIndex& parent) const;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int role);

    virtual QString path(const QModelIndex& index) const;

    virtual const QString localPath(const QModelIndex& index);

    virtual QFileInfo fileInfo(const QModelIndex& index) const;

    virtual QFile* file(const QModelIndex& index) const;

    virtual QDir dir(const QModelIndex& index) const;

private:
    QFileSystemModel m_Model;

};

#endif	/* LOCALFILESYSTEM_H */


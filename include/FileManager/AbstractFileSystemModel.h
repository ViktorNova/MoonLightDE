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

#ifndef ABSTRACTFILESYSTEMMODEL_H
#define	ABSTRACTFILESYSTEMMODEL_H

#include <QAbstractItemModel>

namespace FileManager {

    /**
     * Base class for FileSystemModel implementations.
     */
    class AbstractFileSystemModel : public QAbstractItemModel {
    public:
        virtual QModelIndex index(QString& const_path) = 0;

        virtual QModelIndex index(QString& const_path, QVariant& const_data) = 0;

        virtual QFileIconProvider* iconProvider() = 0;

        virtual QFileInfo fileInfo(QModelIndex const_index) = 0;

        virtual QDir dir(QModelIndex& const_index) = 0;

        virtual QFile file(QModelIndex& const_index) = 0;

        virtual void setIconProvider(QFileIconProvider* provider) = 0;
    };
}

Q_DECLARE_INTERFACE(FileManager::AbstractFileSystemModel, "org.moonlightde.FileManager.AbstractFileSystemModel/1.0")
#endif	/* ABSTRACTFILESYSTEMMODEL_H */
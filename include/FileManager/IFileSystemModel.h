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

#ifndef IFILESYSTEMMDOEL_H
#define	IFILESYSTEMMDOEL_H

#include <QAbstractItemModel>

#include "IItemModelService.h"
#include "INavigationService.h"

namespace FileManager {

    /**
     * Provides a common interface to access the different file systems. Allways
     * resolv it using <code>NavigationService</code>
     */
    class IFileSystemModel : public IItemModelService {
    public:
        /**
         * Resolve the path of the give resource maped to the local file system.
         * @param index
         * @return local resource path or an empthy string.
         */
        virtual const QString localPath(const QModelIndex& index) = 0;

        /**
         * Fetch the information correspoding to the given index. This may point
         * to a "virtual" file or directory.
         */
        virtual QFileInfo fileInfo(const QModelIndex &index) const = 0;

        /**
         * Get a <code>QDir</code> like handler for the given index. This may point
         * to a "virtual" directory.
         */
        virtual QDir dir(const QModelIndex &index) const = 0;

        /**
         * Get a <code>QFile</code> like handler for the given index. This may point
         * to a "virtual" file.
         */
        virtual QFile* file(const QModelIndex &index) const = 0;
    };
}

Q_DECLARE_INTERFACE(FileManager::IFileSystemModel, "org.moonlightde.FileManager.FileSystemModel/1.0")
#endif	/* IFILESYSTEMMDOEL_H */
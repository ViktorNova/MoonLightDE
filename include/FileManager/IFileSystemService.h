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

#ifndef IFILESYSTEMSERVICE_H
#define	IFILESYSTEMSERVICE_H

#include <usServiceInterface.h>

#include <QDir>
#include <QFile>
#include <QVariant>
#include <QFileInfo>
#include <QModelIndex>
#include <QFileIconProvider>
#include <QAbstractItemModel>

namespace FileManager {
    /* Description: Provides a common interface to access the different file 
     *  systems and hides the complexity of handling their implementations.
     * 
     * Example:
     *   #include <usModuleContext.h>
     *   #include <usServiceTracker.h>
     *   #include <usGetModuleContext.h>
     *   ... 
     * 
     *   ModuleContext *context = GetModuleContext();
     *   ServiceTracker<IFileSystemService> * tracker = new ServiceTracker<IFileSystemService>(context);
     *   tracker->Open();
     * 
     *   IFileSystemService* fs = tracker->GetService();
     *   fs->index("smb://localhost/cool stuff");
     *   ...
     * 
     *   tracker->Close()
     *   delete tracker;
     *   
     */
    class IFileSystemService : public QAbstractItemModel {
    public:

        /**
         * Resolve the QModelIndex corresponding to the given path.
         * 
         * @param path the resource path.
         * @return A <code>QModelIndex</code> for to the given path.
         * @throws FileManager::InvalidPath If it isn't possible to open the path 
         *         with none of the registered FileSystemModels.
         * @throws FileManager::AccessDenied If the user doesn't have access to the
         *         specified path.
         */
        virtual QModelIndex index(const QString &path) = 0;

        /**
         * Resolve the QModelIndex corresponding to the given path, the beheavior of
         * the function can be changed by using the data argument. See the file 
         * systems model implementations for details.
         * 
         * @param path the resource path.
         * @param data aditional data passed to the implementations. By example a 
         *        filtering criteria.
         * @return A <code>QModelIndex</code> for to the given path.
         * @throws FileManager::InvalidPath If it isn't possible to open the path 
         *         with none of the registered FileSystemModels.
         * @throws FileManager::AccessDenied If the user doesn't have access to the
         *  specified path.
         */
        virtual QModelIndex index(const QString &path, const QVariant &data) = 0;

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

        /**
         * Fetch the <code>QFileIconProvider</code> registered or <code>NULL</code>.
         */
        virtual QFileIconProvider * iconProvider() const = 0;

        /**
         * Set the <code>QFileIconProvider</code> to be used while presenting the
         * files.
         */
        virtual void setIconProvider(QFileIconProvider * provider) = 0;
    };
}

Q_DECLARE_INTERFACE(FileManager::IFileSystemService, "org.moonlightde.FileManager.IFileSystemService/1.0")
US_DECLARE_SERVICE_INTERFACE(FileManager::IFileSystemService, "org.moonlightde.FileManager.IFileSystemService/1.0")

        
#endif	/* IFILESYSTEMSERVICE_H */


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

#ifndef FILESYSTEMSERVICEIMPL_H
#define	FILESYSTEMSERVICEIMPL_H

#include "FileManager/IFileSystemService.h"
#include "FileManager/IFileSystemModelFactory.h"
#include "FileManager/AbstractFileSystemModel.h"

#include <usServiceReference.h>

using namespace us;
using namespace FileManager;

class FileSystemServiceImpl : public IFileSystemService {
    Q_OBJECT
    Q_INTERFACES(FileManager::IFileSystemService)
public:
    FileSystemServiceImpl(QObject * parent);

    virtual ~FileSystemServiceImpl();

    virtual QModelIndex index(const QString& path);

    virtual QModelIndex index(const QString& path, const QVariant& data);

    virtual QFileInfo fileInfo(const QModelIndex& index) const;

    virtual QDir dir(const QModelIndex& index) const;

    virtual QFile* file(const QModelIndex& index) const;


    virtual QFileIconProvider* iconProvider() const;

    virtual void setIconProvider(QFileIconProvider* provider);
    

    /*
        virtual void addModelFactory(const ServiceReference<IFileSystemModelFactory>& ref, IFileSystemModelFactory* modelFactory);
        virtual void removeModelFactory(const ServiceReference<IFileSystemModelFactory>& ref);
     */
private:
    QFileIconProvider* m_Provider;
    QHash<ServiceReference<IFileSystemModelFactory>, IFileSystemModelFactory*> m_RefToServices;
    QHash<QString, AbstractFileSystemModel *> mounts;
};

#endif	/* FILESYSTEMSERVICEIMPL_H */


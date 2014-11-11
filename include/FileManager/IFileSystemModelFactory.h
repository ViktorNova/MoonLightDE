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

#ifndef FILESYSTEMMODELFACTORY_H
#define	FILESYSTEMMODELFACTORY_H

#include <usServiceInterface.h>
#include <usModuleContext.h>

#include <QString>
#include <QFileSystemModel>
#include <QList>
#include <QAction>

/* Base class for File System Model Factories, it should be used to expose then
 * as services.
 * 
 * In order to ease the filtering you must set as service properties the 
 * "schemes" that the given implementation support.
 * By example:
 *  ServiceProperties props;
 *  props["scheme"] = std::string("file");
 *  context->RegisterService<FileSystemModelFactory>(myFSModelFactory, props);
 * 
 * If the model support several FS you must register the service several times
 * with different schemes.
 */
class IFileSystemModelFactory {
public:

    virtual ~IFileSystemModelFactory() {
    }
    virtual QFileSystemModel * GetModel(QString path) = 0;
    virtual QStringList GetSupportedSchemes() = 0;
    virtual QList<QAction> GetActions(QFileSystemModel * model) = 0;
protected:
    friend class Activator;
    virtual void RegisterService(us::ModuleContext *context) = 0;
};

US_DECLARE_SERVICE_INTERFACE(IFileSystemModelFactory, "org.moonlightde.FileManager.IFileSystemModelFactory/1.0")

#endif	/* FILESYSTEMMODELFACTORY_H */



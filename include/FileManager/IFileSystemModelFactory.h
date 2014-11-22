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


/**
 * This service exists for the propose of providing access to new file systems, 
 * real (cifs, ftp) or virtual (Mi PC, networks://). It should not be used 
 * directly istead use the <code>FileSystemService</code>.
 * 
 * Realization specifications:
 * In order to ease the filtering you must set as service properties the 
 * "schemes" that the given implementation support, by example:
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
    
protected:
    friend class Activator;
    virtual void RegisterService(us::ModuleContext *context) = 0;
};

US_DECLARE_SERVICE_INTERFACE(IFileSystemModelFactory, "org.moonlightde.FileManager.IFileSystemModelFactory/1.0")

#endif	/* FILESYSTEMMODELFACTORY_H */



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

#ifndef IFOLDERVIEWFACTORY_H
#define	IFOLDERVIEWFACTORY_H

#include <usServiceInterface.h>
#include <usModuleContext.h>

#include <QString>
#include <QStringList>
#include <QAbstractItemView>

/* Base class for FolderView Factories, it should be used to expose then
 * as services.
 * 
 * In order to ease the filtering you must set as service properties the 
 * "names" of the implemented views.
 * By example:
 *  ServiceProperties props;
 *  props["name"] = std::string("icon");
 *  context->RegisterService<FileSystemModelFactory>(myViewFactory, props);
 * 
 * If the factory support several FolderViews you must register the service 
 * several times with different names.
 */
class IFolderViewFactory {
public:
    virtual ~IFolderViewFactory() {
    };
    virtual QAbstractItemView* GetView(QString name) = 0;
    virtual QString GetViewFullName(QString name) = 0;

    /* Returns a human readable name for the view name. */
    virtual QStringList GetSupportedViews() = 0;
protected:
    /* Utility function to register the factory as a service. When subclassing
     * in order to allow the access to this function you must set as friend the 
     * caller class.     */
    virtual void RegisterService(us::ModuleContext *context) = 0;
};
US_DECLARE_SERVICE_INTERFACE(IFolderViewFactory, "org.moonlightde.FileManager.IFolderViewFactory/1.0")


#endif	/* IFOLDERVIEWFACTORY_H */


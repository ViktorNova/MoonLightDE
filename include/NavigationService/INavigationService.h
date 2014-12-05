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

#ifndef INAVIGATIONSERVICE_H
#define	INAVIGATIONSERVICE_H

#include "IItemModelService.h"
#include "IFileSystemModel.h"

#include <usServiceReference.h>



#include <QDir>
#include <QFile>
#include <QVariant>
#include <QFileInfo>
#include <QModelIndex>
#include <QFileIconProvider>
#include <QAbstractItemModel>

namespace NavigationService {

    /* Description: Allows to resolve the right ItemModel to handle a given
     *  scheme.
     * 
     * Example:
     * <code>
     *   #include <usModuleContext.h>
     *   #include <usServiceTracker.h>
     *   #include <usGetModuleContext.h>
     *   ... 
     * 
     *   ModuleContext *context = GetModuleContext();
     *   ServiceTracker<INavigationService> * tracker = new ServiceTracker<INavigationService>(context);
     *   tracker->Open();
     * 
     *   INavigationService* fs = tracker->GetService();
     *   IModelService* model = fs->model("tasks");
     *   if (model) {
     *      ...
     *   }
     *   
     * 
     *   tracker->Close()
     *   delete tracker;
     * </code>
     */
    class INavigationService {
    public:
        /**
         * Resolves a model capable to handle the given scheme.
         * @param scheme
         * @return an IItemModelService or NULL
         */
        virtual IItemModelService * model(const QString& scheme) = 0;

        /**
         * Resolves the root model (PC) .
         * @param scheme
         * @return an IItemModelService or NULL
         */
        virtual IItemModelService * root() = 0;

    };
}

Q_DECLARE_INTERFACE(NavigationService::INavigationService, "org.moonlightde.NavigationService.INavigationService/1.0")
US_DECLARE_SERVICE_INTERFACE(NavigationService::INavigationService, "org.moonlightde.NavigationService.INavigationService/1.0")


#endif	/* IFILESYSTEMSERVICE_H */


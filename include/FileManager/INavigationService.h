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

namespace FileManager {

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
        IItemModelService * model(const QString& scheme);

        /**
         * Resolves the root model (PC) .
         * @param scheme
         * @return an IItemModelService or NULL
         */

        IItemModelService * root();


        /**
         * Resolves the path to the given index.
         * @param index
         * @return index path.
         */
        virtual QString path(const QModelIndex& index) const = 0;

    protected:
        friend class ItemModelServicesMonitor;
        std::size_t addModel(const us::ServiceReference<FileManager::IItemModelService> &ref, FileManager::IItemModelService * service);
        std::size_t removeModel(const us::ServiceReference<FileManager::IItemModelService> &ref);

        std::map<us::ServiceReference<FileManager::IItemModelService>, FileManager::IItemModelService *> m_ItemModels;
    };
}

Q_DECLARE_INTERFACE(FileManager::INavigationService, "org.moonlightde.FileManager.INavigationService/1.0")
US_DECLARE_SERVICE_INTERFACE(FileManager::INavigationService, "org.moonlightde.FileManager.INavigationService/1.0")


#endif	/* IFILESYSTEMSERVICE_H */


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

#include "FolderController.h"

#include "Views/BasicFolderViewFactory.h"

#include <NavigationService/IItemModelService.h>

#include <usModule.h>
#include <usModuleContext.h>
#include <usModuleActivator.h>
#include <usServiceProperties.h>

#include <QPointer>
#include <QDebug>

US_USE_NAMESPACE
/**
 */
class Activator : public ModuleActivator {
private:

    /**
     * Implements ModuleActivator::Load().
     *
     * @param context the framework context for the module.
     */
    void Load(ModuleContext* context) {
        qDebug() << "FileManager: Loading.";


        mBasicFolderViewFactory.RegisterService(context);
        mFolderController.SetCurrentPath("/");
        QWidget * ui = NULL;
        ui = mFolderController.GetView();
        if (ui != NULL)
            ui->show();
        else
            qCritical() << "FileManager: Ui wasn\'t built ";
    }

    /**
     * Implements ModuleActivator::Unload().
     *
     * @param context the framework context for the module.
     */
    void Unload(ModuleContext* context) {
        qDebug() << "FileManager: Unloading.";
//        m_Tracker.Close();

    }

    FolderController mFolderController;
    BasicFolderViewFactory mBasicFolderViewFactory;
};

US_EXPORT_MODULE_ACTIVATOR(FileManager, Activator)

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

#include "FileManager/IFileSystemModelFactory.h"
#include "FileManager/IFolderViewFactory.h"

#include <usModuleContext.h>
#include <usServiceReference.h>
#include <usGetModuleContext.h>

#include <QLabel>
#include <QFileSystemModel>
#include <QListView>
#include <QDebug>

FolderController::FolderController() {
    mView = new QWidget();
}

FolderController::~FolderController() {
    delete mView;
}

QUrl FolderController::GetCurrentPath() const {
    return mCurrentPath;
}

void FolderController::SetCurrentPath(QString path) throw (InvalidUriException, UriNotAvailableException) {
    QUrl url;
    url.setUrl(path);
    if (!url.isValid()) {
        InvalidUriException *ex = new InvalidUriException();
        ex->raise();
        return;
    }

    if (!mCurrentModelSupportedSchemes.contains(url.scheme()))
        // Prepare a suitable model for the given path
        BuildFSModel(url.scheme());

    if (!mCurrentModel) {
        qWarning() << "FileManager: FSModel Wasn't created.";
        return;
    }
    mCurrentModel->setRootPath(path);

    if (!mFolderView)
        BuildFSView("icon");

    mFolderView->setModel(mCurrentModel);
    mFolderView->setRootIndex(mCurrentModel->index(path));
    mCurrentPath = path;
}

void FolderController::BuildFSModel(QString scheme) {
    US_USE_NAMESPACE

    ModuleContext *context = GetModuleContext();
    try {
        std::vector<ServiceReference<IFileSystemModelFactory> > refs =
                context->GetServiceReferences<IFileSystemModelFactory>("(scheme=" + scheme.toStdString() + ")");

        if (!refs.empty()) {
            IFileSystemModelFactory * factory = context->GetService<IFileSystemModelFactory>(refs.front());

            if (factory) {
                mCurrentModel = factory->GetModel(scheme);
                mCurrentModelSupportedSchemes = factory->GetSupportedSchemes();
            }
        }
    } catch (std::logic_error &ex) {
        qWarning() << "FileManager: " << ex.what();
    }

}

void FolderController::BuildFSView(QString name) {
    US_USE_NAMESPACE

    ModuleContext *context = GetModuleContext();
    try {
        std::vector<ServiceReference<IFolderViewFactory> > refs =
                context->GetServiceReferences<IFolderViewFactory>("(name=" + name.toStdString() + ")");

        if (!refs.empty()) {
            IFolderViewFactory * factory = context->GetService<IFolderViewFactory>(refs.front());

            if (factory) {
                mFolderView = factory->GetView(name);
                mFolderViewName = name;
            }
        }
    } catch (std::logic_error &ex) {
        qWarning() << "FileManager: " << ex.what();
    }
}

QFileSystemModel* FolderController::GetModel() const {
    return mCurrentModel;
}

QWidget* FolderController::GetView() const {
    if (mFolderView)
        return mFolderView;
    else
        return mView;
}
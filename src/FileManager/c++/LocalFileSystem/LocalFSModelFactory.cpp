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

#include "LocalFSModelFactory.h"

#include <usModuleContext.h>
#include <usServiceProperties.h>


#include <QFileSystemModel>

LocalFSModelFactory::LocalFSModelFactory() {
    supportedSchemes << QString("file") << QString("");
}

LocalFSModelFactory::~LocalFSModelFactory() {
}

QFileSystemModel * LocalFSModelFactory::GetModel(QString path) {
    QFileSystemModel *model = new QFileSystemModel();
    model->setRootPath(path);
    model->setReadOnly(false);
    return model;
}

QStringList LocalFSModelFactory::GetSupportedSchemes() {
    return supportedSchemes;
}

void LocalFSModelFactory::RegisterService(us::ModuleContext *context) {
    US_USE_NAMESPACE
    ServiceProperties props1;
    props1["scheme"] = std::string("file");
    context->RegisterService<IFileSystemModelFactory>(this, props1);

    ServiceProperties props2;
    props2["scheme"] = std::string("");
    context->RegisterService<IFileSystemModelFactory>(this, props2);
}

QList<QAction> LocalFSModelFactory::GetActions(QFileSystemModel * model) {
//    QAction *copy = 
}
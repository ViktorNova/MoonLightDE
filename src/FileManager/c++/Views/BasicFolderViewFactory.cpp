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

#include "BasicFolderViewFactory.h"

#include <Qt>
#include <QListView>
#include <QStyledItemDelegate>

BasicFolderViewFactory::BasicFolderViewFactory() {
    mSupportedViews["icon"] = "Icons";
}

BasicFolderViewFactory::~BasicFolderViewFactory() {
}

QAbstractItemView* BasicFolderViewFactory::GetView(QString name) {
    if (name == "icon") {
        QListView *view = new QListView();
        
        view->setViewMode(QListView::IconMode);
        view->setSpacing(20);
        view->setIconSize(QSize(48, 48));
        
        // TODO: Implement an item delegate to give a correct size to the
        //  items.
        view->setUniformItemSizes(true);
        view->setWrapping(true);

        view->setTextElideMode(Qt::ElideMiddle);
        view->setWordWrap(true);
        
        view->setMovement(QListView::Static);
        view->setResizeMode(QListView::Adjust);
        view->setSelectionMode(QAbstractItemView::ContiguousSelection);
        
        view->setLayoutMode(QListView::Batched);
        view->setBatchSize(10);
        return view;
    }
}

QStringList BasicFolderViewFactory::GetSupportedViews() {
    return mSupportedViews.values();
}

QString BasicFolderViewFactory::GetViewFullName(QString name) {
    if (mSupportedViews.contains(name))
        return mSupportedViews[name];
    else
        return QString();
}

void BasicFolderViewFactory::RegisterService(us::ModuleContext *context) {
    US_USE_NAMESPACE
    ServiceProperties props;
    props["name"] = std::string("icon");
    context->RegisterService<IFolderViewFactory>(this, props);
}
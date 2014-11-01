/* 
 * File:   BasicFolderViewFactory.cpp
 * Author: alexis
 * 
 * Created on 1 de noviembre de 2014, 13:55
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
        
        // TODO: Implement an item delegate to give an apropiated size to the
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
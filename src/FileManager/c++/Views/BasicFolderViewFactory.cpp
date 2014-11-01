/* 
 * File:   BasicFolderViewFactory.cpp
 * Author: alexis
 * 
 * Created on 1 de noviembre de 2014, 13:55
 */

#include "BasicFolderViewFactory.h"

#include <QListView>

BasicFolderViewFactory::BasicFolderViewFactory() {
    mSupportedViews["icon"] = "Icons";
}

BasicFolderViewFactory::~BasicFolderViewFactory() {
}

QAbstractItemView* BasicFolderViewFactory::GetView(QString name) {
    if (name == "icon") {
        QListView *view = new QListView();
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
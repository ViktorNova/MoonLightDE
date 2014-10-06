/*
 * Copyright (C) 2014 Moonlight Desktop Environment Team
 * Authors:
 *      Alexis López Zubieta
 *      Jorge Fernández Sánchez
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


#include "Dash.h"
#include "AppButton.h"
#include "GridLayoutHExpanding.h"
#include "GridLayoutVExpanding.h"
#include "qevent.h"
#include "qdir.h"
#include "core/ModuleSettings.h"

#include <qt5xdg/XdgDesktopFile>

#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QRect>
#include <QLabel>
#include <QTime>
#include <usGetModuleContext.h>

#include <QThread>

#include <algorithm>
#include <CppMicroServices/usModuleContext.h>

/**
 * As XdgDesktopFile doesn't provides the opperator < we must implement it here.
 */
struct XdgDesktopFileComparisonFunctor {

    bool
    operator()(const XdgDesktopFile * __x, const XdgDesktopFile * __y) const {
        return __x->name() < __y->name();
    }
};

Dash::Dash() : m_settings("panel-dash_xdg") {
    m_ui.setupUi(this);
    setWindowFlags(Qt::Popup);
    setFrameStyle(QFrame::NoFrame);
    built = false;
    qsettings = new QSettings(qApp->organizationName(), qApp->applicationName(), this);
    getFavorites();
}

Dash::~Dash() {
}

void Dash::build() {
    QTime time;
    time.start();
    
    const QRect screen = qApp->desktop()->screenGeometry();

    const QSize iconSize(64, 64);
    const QSize boxSize(100, 100);
    const int maxColumnApps = m_ui.tabs->size().width() / (boxSize.width() + 32);
    GridLayoutVExpanding* layoutApps = new GridLayoutVExpanding(maxColumnApps, m_ui.tabApps);

    layoutApps->setSpacing(0);
    layoutApps->setMargin(16);

    GridLayoutVExpanding* layoutSettings = new GridLayoutVExpanding(maxColumnApps, m_ui.tabSettings);

    layoutSettings->setSpacing(0);
    layoutSettings->setMargin(16);

    qDebug() << "Layouts init: " << time.elapsed();
    // Individual items are released inside the AppButton class
    QList<XdgDesktopFile*> appList = XdgDesktopFileCache::getAllFiles();
    std::sort(appList.begin(), appList.end(), XdgDesktopFileComparisonFunctor());
    //    qSort(appList.begin(), appList.end());
    qDebug() << "XdgDesktopFile lockup: " << time.elapsed();

    foreach(XdgDesktopFile * app, appList) {
        if (app->type() != XdgDesktopFile::ApplicationType) {
            delete app;
            continue;
        }
        AppButton *bttn = new AppButton(app, this);

        QLabel *label = new QLabel(app->name());

        //Connecting AppButton with Dash slot
        connect(bttn, &AppButton::pushFavorites, this, &Dash::addFavorites);

        label->setWordWrap(true);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        label->setMaximumSize(boxSize.width(), 35);
        label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        bttn->setFlat(true);
        bttn->setIconSize(iconSize);
        bttn->setMinimumSize(boxSize);
        bttn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        connect(bttn, &AppButton::released, this, &Dash::hide);

        //Layout for widget
        QVBoxLayout* vBoxLayout = new QVBoxLayout();
        vBoxLayout->addWidget(bttn);
        vBoxLayout->addWidget(label);

        QString appCategories = app->value("Categories", "None").toString();

        if (appCategories.contains("Settings", Qt::CaseInsensitive)) {

            layoutSettings->addLayout(vBoxLayout);
        } else {

            layoutApps->addLayout(vBoxLayout);
        }
    }
    qDebug() << "Layouts built: " << time.elapsed();

    qDebug() << "appcontainerSize" << m_ui.tabs->size();

    m_ui.apps->setGeometry(0, 0, m_ui.scrollArea->size().width() - (layoutApps->spacing() * maxColumnApps)
            , layoutApps->getCurrentRow() * boxSize.height());
    m_ui.apps->setLayout(layoutApps);


    m_ui.settings->setGeometry(0, 0, m_ui.scrollAreaSettings->size().width()
            , layoutApps->getCurrentRow() * boxSize.height());
    m_ui.settings->setLayout(layoutSettings);

}

void Dash::free() {

}

void Dash::onItemTrigerred() {
    //    XdgCachedMenuAction* action = static_cast<XdgCachedMenuAction*> (sender());
    //    XdgDesktopFile df;
    //    char* desktop_file = menu_cache_item_get_file_path(action->item());
    //    df.load(desktop_file);
    //    g_free(desktop_file);
    //    df.startDetached();
}

// taken from libqtxdg: XdgMenuWidget
// taken from libqtxdg: XdgMenuWidget

void Dash::handleMouseMoveEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton)
        return;

    //    if ((event->pos() - mDragStartPosition).manhattanLength() < QApplication::startDragDistance())
    //        return;
    //
    //    XdgCachedMenuAction *a = qobject_cast<XdgCachedMenuAction*>(actionAt(event->pos()));
    //    if (!a)
    //        return;
    //
    //    QList<QUrl> urls;
    //    char* desktop_file = menu_cache_item_get_file_path(a->item());
    //    urls << QUrl(desktop_file);
    //    g_free(desktop_file);
    //
    //    QMimeData *mimeData = new QMimeData();
    //    mimeData->setUrls(urls);
    //
    //    QDrag *drag = new QDrag(this);
    //    drag->setMimeData(mimeData);
    //    drag->exec(Qt::CopyAction | Qt::LinkAction);
}

void Dash::showEvent(QShowEvent * event) {
    qDebug() << "Show event";

    if (!built) {
        build();
        built = true;
    }

    m_ui.tabs->setCurrentWidget(m_ui.tabStart);
    show();
}

void Dash::addFavorites(XdgDesktopFile* app) {
    
    us::ModuleContext* context = us::GetModuleContext();
    const QString ruta(ModuleSettings::getModuleDataLocation(context));

    const QString appName(app->fileName());
    QDir* dir = new QDir(ruta);
    dir->mkdir("favs");
    QFile* file = new QFile(appName);
    if (file->copy(dir->absolutePath() + "/favs/" + app->name().toLower())) {
        qDebug() << "Archivo copiado";
    } else {
        qDebug() << "Error";
    }
}

//Get all favorite apps in the directory and paint them on start widget
void Dash::getFavorites() {
    
    us::ModuleContext* context = us::GetModuleContext();
    const QString ruta(ModuleSettings::getModuleDataLocation(context) + "/favs");
    
    qDebug() << "Ruta: " << endl;
    qDebug() << ruta;
    QDir* favsDir = new QDir(ruta);

    QFileInfoList list = favsDir->entryInfoList(QDir::Files, QDir::Name);
    QList<XdgDesktopFile*> favAppList;

    if (!list.empty()) {

        foreach(QFileInfo app, list) {
            const QString cadena(app.filePath());
            //You have to specify the absolute path to the file, otherwise it wont work
            XdgDesktopFile* fav = XdgDesktopFileCache::getFile(cadena);
            favAppList.append(fav);
        }
    }
    //Call method putFavorites
    putFavorites(favAppList);
}

//jfsanchez@estudiantes.uci.cu

void Dash::hideEvent(QHideEvent *event) {
    qDebug() << "hideEvent()";
    QThread::msleep(1);
    QFrame::hideEvent(event);
}

void Dash::putFavorites(QList<XdgDesktopFile*> favAppList) {
    //Rendering widget :P
    const QSize iconSize(64, 64);
    const QSize boxSize(80, 80);
    const int maxColumnApps = m_ui.start->size().width() / (boxSize.width() + 32);
    GridLayoutVExpanding* layoutFavs = new GridLayoutVExpanding(maxColumnApps, m_ui.start);

    layoutFavs->setSpacing(0);
    layoutFavs->setMargin(16);

    // Individual items are released inside the AppButton class

    foreach(XdgDesktopFile* app, favAppList) {
        if (app->type() != XdgDesktopFile::ApplicationType) {
            delete app;
            continue;
        }
        AppButton* bttn = new AppButton(app, true, this);

        QLabel* label = new QLabel(app->name());

        //Connecting AppButton with Dash slot
        connect(bttn, &AppButton::removeFavorites, this, &Dash::removeFavorites);

        label->setWordWrap(true);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        label->setMaximumSize(boxSize.width(), 35);
        label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

        bttn->setFlat(true);
        bttn->setIconSize(iconSize);
        bttn->setMinimumSize(boxSize);
        bttn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        connect(bttn, &AppButton::released, this, &Dash::hide);

        //Layout for widget
        QVBoxLayout* vBoxLayout = new QVBoxLayout();
        vBoxLayout->addWidget(bttn);
        vBoxLayout->addWidget(label);

        layoutFavs->addLayout(vBoxLayout);
    }
}

//TODO: Dinamically update the start widget showing|unshowing the favorites
void Dash::removeFavorites(XdgDesktopFile* app) {
    
    qDebug() << "Certainly YOU SHALL NOT PASS!!!!";
    us::ModuleContext* context = us::GetModuleContext();
    const QString ruta(ModuleSettings::getModuleDataLocation(context) + "/favs");
    
    QDir* favsDir = new QDir(ruta);

    QFileInfoList list = favsDir->entryInfoList(QDir::Files, QDir::Name);

    foreach(QFileInfo file, list) {
//        qDebug() << file.fileName();
//        qDebug() << app->name();
        if(file.fileName() == app->name().toLower()) {
            qDebug() << "You should buy a pet :P";
            const QString ruta(app->fileName());
            QFile* archive = new QFile(ruta);
            archive->remove();
        }
    }
}
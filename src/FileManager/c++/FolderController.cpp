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
#include "ChoseApplicationController.h"


#include "FileManager/IFolderViewFactory.h"
#include "LocalFileSystem/CopyTask.h"

#include <usModuleContext.h>
#include <usServiceReference.h>
#include <usGetModuleContext.h>

#include <Qt>
#include <QUrl>
#include <QLabel>
#include <QListView>
#include <QFileInfo>
#include <QMimeData>
#include <QAction>
#include <QClipboard>
#include <QApplication>
#include <QKeySequence>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QAbstractItemModel>
#include <QFile>
#include <QMimeData>

#include <QDebug>

FolderController::FolderController() : mView(NULL), mCurrentModel(NULL), mFolderView(NULL) {
    mView = new QWidget();

    m_NavigationServiceTracker = new us::ServiceTracker<NavigationService::INavigationService>(us::GetModuleContext());
    m_NavigationServiceTracker->Open();
    
    mOpen = new QAction(tr("Open"), this);
    mOpen->setShortcut(QKeySequence(Qt::Key_Return));
    connect(mOpen, SIGNAL(triggered()), this, SLOT(OnOpen()));

    mNew = new QAction(tr("New"), this);
    mNew->setShortcut(QKeySequence::New);
    connect(mNew, SIGNAL(triggered()), this, SLOT(OnNew()));


    mCopy = new QAction(tr("Copy"), this);
    mCopy->setShortcut(QKeySequence::Copy);
    connect(mCopy, SIGNAL(triggered()), this, SLOT(OnCopy()));

    mCut = new QAction(tr("Cut"), this);
    mCut->setShortcut(QKeySequence::Cut);
    connect(mCut, SIGNAL(triggered()), this, SLOT(OnCut()));

    mPaste = new QAction(tr("Paste"), this);
    mPaste->setShortcut(QKeySequence::Paste);
    connect(mPaste, SIGNAL(triggered()), this, SLOT(OnPaste()));

    mFileOpsGroup = new QActionGroup(this);
    mFileOpsGroup->addAction(mPaste);
    mFileOpsGroup->addAction(mCut);
    mFileOpsGroup->addAction(mCopy);


    mRemove = new QAction(tr("Remove"), this);
    mRemove->setShortcut(QKeySequence::Delete);
    connect(mRemove, SIGNAL(triggered()), this, SLOT(OnRemove()));

    mProperties = new QAction(tr("Properties"), this);
    mProperties->setShortcut(QKeySequence(Qt::ALT + Qt::Key_Return));
    connect(mProperties, SIGNAL(triggered()), this, SLOT(OnShowProperties()));

    mReturn = new QAction(tr("Go Up"), this);
    mReturn->setMenuRole(QAction::NoRole);
    mReturn->setShortcut(QKeySequence(Qt::Key_Backspace));
    connect(mReturn, SIGNAL(triggered()), this, SLOT(OnReturn()));
}

FolderController::~FolderController() {
    delete mView;

    delete mCurrentModel;
    delete mFolderView;

    delete mOpen;
    delete mCopy;
    delete mCut;
    delete mPaste;
    delete mRemove;
    delete mProperties;
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

    //    if (!mCurrentModelSupportedSchemes.contains(url.scheme()))
    //        // Prepare a suitable model for the given path
    //        BuildFSModel(url.scheme());

    NavigationService::INavigationService *service = m_NavigationServiceTracker->GetService();
    if (service)
        mCurrentModel = service->model(url.scheme());

    if (!mCurrentModel) {
        qWarning() << "FileManager: FSModel wasn't created.";
        return;
    }

    if (!mFolderView)
        BuildFSView("icon");

    if (!mFolderView) {
        qWarning() << "FileManager: FolderView wasn't created.";
        return;
    }
    mFolderView->setModel(mCurrentModel->effectiveModel());
    mFolderView->setRootIndex(mCurrentModel->index(path));
    mCurrentPath = path;

    mFolderView->setContextMenuPolicy(Qt::ActionsContextMenu);

    mFolderView->addAction(mOpen);
    mFolderView->addAction(mNew);
    mFolderView->addAction(mCopy);
    mFolderView->addAction(mCut);
    mFolderView->addAction(mPaste);
    mFolderView->addAction(mRemove);
    mFolderView->addAction(mProperties);
    mFolderView->addAction(mReturn);

    UpdateWidgetActions();
    connect(mFolderView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &FolderController::UpdateWidgetActions);
}

void FolderController::UpdateWidgetActions() {

    bool filesSelected = !mFolderView->selectionModel()->selection().empty();
    mOpen->setVisible(filesSelected);
    mRemove->setVisible(filesSelected);

    mNew->setVisible(!filesSelected);

    bool isReadOnly = /*mCurrentModel->isReadOnly()*/ false;
    mCut->setDisabled(isReadOnly);
    mRemove->setDisabled(isReadOnly);

    QClipboard *clipboard = QApplication::clipboard();

    const QMimeData *data = clipboard->mimeData();
    if (data->hasUrls()) {
        qDebug() << "FileManager: Clipboard data: " << data->urls();
        mPaste->setDisabled(isReadOnly);
    }

}

void FolderController::BuildFSModel(QString scheme) {
    US_USE_NAMESPACE
    //    ModuleContext *context = GetModuleContext();
    //    try {
    //        std::vector<ServiceReference<IFileSystemModelFactory> > refs =
    //                context->GetServiceReferences<IFileSystemModelFactory>("(scheme=" + scheme.toStdString() + ")");
    //
    //        if (!refs.empty()) {
    //            IFileSystemModelFactory * factory = context->GetService<IFileSystemModelFactory>(refs.front());
    //
    //            if (factory) {
    //                mCurrentModel = factory->GetModel(scheme);
    //                mCurrentModelSupportedSchemes = factory->GetSupportedSchemes();
    //            }
    //        }
    //    } catch (std::logic_error &ex) {
    //        qWarning() << "FileManager: " << ex.what();
    //    }

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

    connect(mFolderView, &QAbstractItemView::doubleClicked, this, &FolderController::OnOpen);
}

QAbstractItemModel* FolderController::GetModel() const {
    return mCurrentModel->effectiveModel();
}

QWidget* FolderController::GetView() const {
    if (mFolderView)
        return mFolderView;
    else
        return mView;
}

void FolderController::OnOpen() {
    Q_ASSERT(mFolderView != NULL);
    QModelIndexList selection = mFolderView->selectionModel()->selectedIndexes();

    //    if (selection.count() == 1) {
    //        if (mCurrentModel->fisDir(selection.first()))
    //            mFolderView->setRootIndex(selection.first());
    //        else {
    //            bool fail = !QDesktopServices::openUrl(QUrl::fromLocalFile(mCurrentModel->filePath(selection.first())));
    //
    //            if (fail) {
    //
    //                //                ChoseApplicationController *chooser = new ChoseApplicationController(mCurrentModel->mimeTypes(selection.first()).first());
    //                qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " open unknown files not supported yet.";
    //            }
    //        }
    //    }

    if (selection.count() > 1) {
        qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " open multiple items not supported.";
        return;
    }
    qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " no items selected.";
}

void FolderController::OnNew() {
    qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " not implemented yet.";
}

void FolderController::OnCopy() {
    // Fetch selected files
    QList<QUrl> urls;
    QModelIndexList selection = mFolderView->selectionModel()->selectedIndexes();

    //    foreach(QModelIndex modelIndex, selection) {
    //        urls << QUrl::fromUserInput(mCurrentModel->filePath(modelIndex));
    //    }


    QClipboard *clipboard = QApplication::clipboard();
    clipboard->clear();
    QMimeData *data = new QMimeData();
    data->setUrls(urls);
    clipboard->setMimeData(data);
    qDebug() << "FileManager: Files copied to clipboard: " << urls;
    mCutFlag = false;
}

void FolderController::OnCut() {
    OnCopy();
    mCutFlag = true;
}

void FolderController::OnPaste() {
    qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " not fully implemented yet.";
    QClipboard *clipboard = QApplication::clipboard();

    const QMimeData *data = clipboard->mimeData();
    if (data->hasUrls()) {
        qDebug() << "FileManager: Clipboard data: " << data->urls();


        QString currentPath = mCurrentModel->path(mFolderView->rootIndex());
        qDebug() << "FileManager: Current path: " << currentPath;
        CopyTask *task = new CopyTask(data->urls(), QUrl::fromUserInput(currentPath), this);
        task->Start();
    }

    if (mCutFlag) { // Remove files on cut

        foreach(QUrl url, data->urls()) {
            QFile::remove(url.toLocalFile());
        }
        mCutFlag = false;
    }
}

void FolderController::OnRemove() {
    // Fetch selected files
    QModelIndexList selection = mFolderView->selectionModel()->selectedIndexes();

    foreach(QModelIndex modelIndex, selection) {
        QFile::remove(mCurrentModel->path(modelIndex));
    }
}

void FolderController::OnShowProperties() {
    qDebug() << "FileManager: " << __PRETTY_FUNCTION__ << " not implemented yet.";
}

void FolderController::OnReturn() {
//    FileManager::IFileSystemModel * fsModel = dynamic_cast<FileManager::IFileSystemModel *>(mCurrentModel);
//    if (fsModel) {
//        QDir current = fsModel->fileInfo(mFolderView->rootIndex()).dir();
//
//        mFolderView->setRootIndex(mCurrentModel->index(current.path()));
//    }
}
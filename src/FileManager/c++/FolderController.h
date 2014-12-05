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

#ifndef FOLDERCONTROLLER_H
#define	FOLDERCONTROLLER_H

#include "Exceptions/InvalidUriException.h"
#include "Exceptions/UriNotAvailableException.h"

#include <NavigationService/INavigationService.h>

#include <usServiceTracker.h>

#include <QUrl>
#include <QString>
#include <QWidget>
#include <QAction>
#include <QObject>
#include <QPointer>
#include <QActionGroup>
#include <QAbstractItemView>
#include <QFileSystemModel>

class FolderController : public QObject {
    Q_OBJECT
public:
    FolderController();
    FolderController(const FolderController& orig);
    virtual ~FolderController();

    QUrl GetCurrentPath() const;

    /* Description: Validates the path, attempts to fetch files and folders at 
     *  the given path updating the model and also the view. In case of failure
     *  is thrown one of these exceptions: InvalidUriException, 
     *  UriNotAvailableException. This task is executed in a thread so it will 
     *  not produce blocking in the UI.
     */
    void SetCurrentPath(QString path) throw (InvalidUriException, UriNotAvailableException);

    QAbstractItemModel * GetModel() const;

    /* Description: Returns a widget with the current folder view or a message
     *  for the user if the Folder view it's not ready or if an error ocurred.
     *  It will always return a valid QWidget.
     */
    QWidget* GetView() const;

public slots:
    void UpdateWidgetActions();
    
    // File Operations
    void OnNew();
    void OnCopy();
    void OnCut();
    void OnPaste();
    void OnRemove();
    void OnShowProperties();
    
    // Navigation
    void OnOpen();
    void OnReturn();
    
protected:
    /* Description: Build a model for the given scheme. The models are taken 
     * from the models factories that were exported as services.
     */
    void BuildFSModel(QString scheme);
    void BuildFSView(QString name);

private:
    QUrl mCurrentPath;
    QWidget * mView;
    NavigationService::IItemModelService * mCurrentModel;
    QStringList mCurrentModelSupportedSchemes;
    QAbstractItemView * mFolderView;
    QString mFolderViewName;
    us::ServiceTracker<NavigationService::INavigationService> * m_NavigationServiceTracker;
    
    bool mCutFlag;
    // Default Actions
    QAction *mOpen, *mNew, *mCopy, *mCut, *mPaste, *mRemove, *mProperties, *mReturn;
    QActionGroup *mFileOpsGroup;
};

#endif	/* FOLDERCONTROLLER_H */


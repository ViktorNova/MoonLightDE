/* 
 * File:   LocalFileSystemService.h
 * Author: alexis
 *
 * Created on 27 de noviembre de 2014, 11:19
 */

#ifndef LOCALFILESYSTEMSERVICE_H
#define	LOCALFILESYSTEMSERVICE_H

#include "FileManager/AbstractFileSystemModel.h"

#include <QFileSystemModel>

class LocalFileSystemService : public FileManager::AbstractFileSystemModel{
    Q_OBJECT
    Q_INTERFACES(FileManager::AbstractFileSystemModel)
public:
    LocalFileSystemService();
    virtual ~LocalFileSystemService();
    

    

private:
    QFileSystemModel model;
};

#endif	/* LOCALFILESYSTEMSERVICE_H */


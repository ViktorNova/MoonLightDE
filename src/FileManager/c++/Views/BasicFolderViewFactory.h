/* 
 * File:   BasicFolderViewFactory.h
 * Author: alexis
 *
 * Created on 1 de noviembre de 2014, 13:55
 */

#ifndef BASICFOLDERVIEWFACTORY_H
#define	BASICFOLDERVIEWFACTORY_H

#include "FileManager/IFolderViewFactory.h"

#include <QHash>

class BasicFolderViewFactory : public IFolderViewFactory {
public:
    BasicFolderViewFactory();
    virtual ~BasicFolderViewFactory();

    QAbstractItemView* GetView(QString name);
    QStringList GetSupportedViews();
    QString GetViewFullName(QString name);
protected:
    friend class Activator;
    void RegisterService(us::ModuleContext *context);
private:
    QHash<QString, QString> mSupportedViews;

};

#endif	/* BASICFOLDERVIEWFACTORY_H */


/* 
 * File:   ApplicationListModel.h
 * Author: alexis
 *
 * Created on 4 de noviembre de 2014, 16:10
 */

#ifndef APPLICATIONLISTMODEL_H
#define	APPLICATIONLISTMODEL_H

#include <QList>
#include <XdgDesktopFile>
#include <QAbstractListModel>

class ApplicationListModel : public QAbstractListModel {
    Q_OBJECT
public:
    ApplicationListModel(const QString & mimeType);
    virtual ~ApplicationListModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
private:
    QList<XdgDesktopFile*> list;
};

#endif	/* APPLICATIONLISTMODEL_H */


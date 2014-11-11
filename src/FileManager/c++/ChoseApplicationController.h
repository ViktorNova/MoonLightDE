/* 
 * File:   ChoseApplicationView.h
 * Author: alexis
 *
 * Created on 4 de noviembre de 2014, 16:01
 */

#ifndef _CHOSEAPPLICATIONCONTROLLER_H
#define	_CHOSEAPPLICATIONCONTROLLER_H

#include "ui_ChoseApplicationView.h"
#include "Models/ApplicationListModel.h"
#include <XdgDesktopFile>

class ChoseApplicationController : public QWidget {
    Q_OBJECT
public:
    ChoseApplicationController(const QString &mimeType, QAction * action);
    virtual ~ChoseApplicationController();

public slots:
    void OnItemChosen(const QModelIndex & index);
    void focusOutEvent(QFocusEvent * event);

private:
    Ui::ChoseApplicationView widget;

    ApplicationListModel* mModel;
    QAction * mAction;
};

#endif	/* _CHOSEAPPLICATIONCONTROLLER_H */

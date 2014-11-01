/* 
 * File:   MessageView.h
 * Author: alexis
 *
 * Created on 30 de octubre de 2014, 10:21
 */

#ifndef _MESSAGEVIEW_H
#define	_MESSAGEVIEW_H

#include "ui_MessageView.h"

#include <QString>
#include <QList>
#include <QAction>

class MessageView : public QWidget {
    Q_OBJECT
public:
    MessageView(QString message, QList<QAction* > actions);
    virtual ~MessageView();
private:
    Ui::MessageView widget;
};

#endif	/* _MESSAGEVIEW_H */

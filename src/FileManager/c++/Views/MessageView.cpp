/*
 * File:   MessageView.cpp
 * Author: alexis
 *
 * Created on 30 de octubre de 2014, 10:21
 */

#include "MessageView.h"

#include <QToolButton>

MessageView::MessageView(QString message, QList<QAction *> actions) {
    widget.setupUi(this);

    widget.MessageLabel->setText(message);

    // TODO: Check correct emplacement of buttons
    foreach(QAction* action, actions) {
        QToolButton * bttn = new QToolButton(this);
        bttn->setDefaultAction(action);
        widget.actionsLayout->addWidget(bttn);
    }

}

MessageView::~MessageView() {
}

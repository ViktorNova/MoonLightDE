/*
 * File:   ChoseApplicationView.cpp
 * Author: alexis
 *
 * Created on 4 de noviembre de 2014, 16:01
 */

#include "ChoseApplicationController.h"

#include <QToolButton>

ChoseApplicationController::ChoseApplicationController(const QString &mimeType, QAction * action) {
    widget.setupUi(this);

    mModel = new ApplicationListModel(mimeType);
    widget.listView->setModel(mModel);

    connect(widget.listView, SIGNAL(clicked()), this, SLOT(OnItemChosen()));
    mAction = action;

    QToolButton *bttn = new QToolButton(this);
    bttn->setDefaultAction(mAction);
    widget.verticalLayout->addWidget(bttn);

    connect(widget.listView, SIGNAL(clicked()), this, SLOT(OnItemChosen()));
}
void ChoseApplicationController::focusOutEvent(QFocusEvent * event) {
    hide();
    QWidget::focusOutEvent(event);
    deleteLater();
}

ChoseApplicationController::~ChoseApplicationController() {
    delete mModel;
}

void ChoseApplicationController::OnItemChosen(const QModelIndex & index) {
    emit(mAction->triggered(false));
}

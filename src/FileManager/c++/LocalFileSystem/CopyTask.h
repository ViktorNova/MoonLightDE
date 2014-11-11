/* 
 * File:   CopyTask.h
 * Author: alexis
 *
 * Created on November 5, 2014, 1:52 PM
 */

#ifndef COPYTASK_H
#define	COPYTASK_H

#include "FileManager/Task.h"

#include <QObject>
#include <QUrl>
#include <QList>
#include <QDataStream>

class CopyTask : public QObject, public FileManager::Task {
    Q_OBJECT
    Q_INTERFACES(FileManager::Task)
    enum States {
        READY,
        WORKING,
        FINISHED,
        STALLED
    };

public:
    CopyTask(QList<QUrl> files, QUrl destination, QObject * parent = 0);
    virtual ~CopyTask();

    virtual int GetId() const;

    virtual QString GetDescription();

    virtual bool IsRunning();


public slots:
    virtual void Stop();
    virtual void Start();


    virtual void ProcessFile(QString src, QString target);

signals:
    void started();
    void stopped();

protected:
    virtual void SetId(int id);

private:
    int mId;
    States mState;
    QList<QUrl> mFiles;
    QUrl mDestination;
    bool mStopReqested;

    int mCurrent;
    QDataStream *in;
    QDataStream *out;
};

#endif	/* COPYTASK_H */


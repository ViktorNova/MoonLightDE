/* 
 * File:   CopyTask.h
 * Author: alexis
 *
 * Created on November 5, 2014, 1:52 PM
 */

#ifndef COPYTASK_H
#define	COPYTASK_H

#include "FileManager/Task.h"

#include <QStringList>

class CopyTask : public FileManager::Task {
public:
    CopyTask(QStringList files, QString destination);
    virtual ~CopyTask();

    virtual int GetId() const;

    virtual void run();


    
protected:
    virtual void SetId(int id);

private:
    int mId;
    bool running;
    bool paused;
    QStringList mFiles;
    QString mDestination;
    QString mCurrent;

};

#endif	/* COPYTASK_H */


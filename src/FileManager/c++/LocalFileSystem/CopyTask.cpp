/* 
 * File:   CopyTask.cpp
 * Author: alexis
 * 
 * Created on November 5, 2014, 1:52 PM
 */

#include "CopyTask.h"


#include <QFile>

#include <QDir>
#include <QDataStream>
#include <QEventLoop>
#include <QApplication>
#include <QDebug>

using namespace FileManager;

CopyTask::CopyTask(QList<QUrl> files, QUrl destination, QObject * parent) : QObject(parent), Task(), mStopReqested(false) {
    mFiles = files;
    mDestination = destination;
    mState = READY;
}

CopyTask::~CopyTask() {

}

void CopyTask::SetId(int id) {
    mId = id;
}

int CopyTask::GetId() const {
    return mId;
}

void CopyTask::ProcessFile(QString src, QString target) {

    QFile inFile(src);
    if (!inFile.open(QIODevice::ReadOnly)) {
        mState = STALLED;
        return;
    }
    QFile outFile(target);
    if (!outFile.open(QIODevice::WriteOnly)) {
        mState = STALLED;
        return;
    }

    QDataStream in(&inFile);
    QDataStream out(&outFile);

    char buffer[512];

    bool eof = false, error = false;

    int readBytes = 0, writeBytes = 0;
    while (!in.atEnd() && !error) {
        readBytes = in.readRawData(buffer, 512);
        if (readBytes == -1) {
            error = true;
            break;
        }
        writeBytes = out.writeRawData(buffer, readBytes);
        if (writeBytes != readBytes) {
            error = true;
            break;
        }
    }
}

void CopyTask::Stop() {
    mStopReqested = true;
}

void CopyTask::Start() {
    mState = WORKING;
    mCurrent = 0;

    emit started();

    foreach(QUrl path, mFiles) {
        if (mStopReqested) {
            mState = FINISHED;
            emit stopped();
        }
        QDir org(path.toLocalFile());
        QDir dest(mDestination.toLocalFile());
        if (!org.exists(path.toLocalFile()) ) {
            qDebug() << "FileManager: Fail to copy " << org.path() << ", doesn't exist.";
            return;
        }
//        if (!org.isReadable()) {
//            qDebug() << "FileManager: Fail to copy " << path.toLocalFile() << ", is not readable.";
//            return;
//        }
//        
        // TODO: provide a better file copy implementation
        //        ProcessFile(path, mDestination);
        if (!QFile::copy(org.path(), dest.path() + "/" + org.dirName()))
            qDebug() << "FileManager: Fail to copy to " << dest.path() + "/" + org.dirName();
        else
            qDebug() << "FileManager: File copied to " << dest.path() + "/" + org.dirName();
        qApp->processEvents();

        mCurrent++;
    }
    mState = WORKING;
    emit stopped();
}

QString CopyTask::GetDescription() {
    switch (mState) {
        case READY:
            return QString("Ready to copy");
        case WORKING:
            return QString("Coping " + mFiles.at(mCurrent).toString());
        case STALLED:
            return QString("Error");
        default:
            return QString("Copy task");
    }
}

bool CopyTask::IsRunning() {
    if (mState == WORKING)
        return true;
    else
        return false;
}
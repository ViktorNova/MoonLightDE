/* 
 * File:   CopyTask.cpp
 * Author: alexis
 * 
 * Created on November 5, 2014, 1:52 PM
 */

#include "CopyTask.h"

using namespace FileManager;

CopyTask::CopyTask(QStringList files, QString destination) : Task() {
    mFiles = files;
    mDestination = destination;
}

CopyTask::~CopyTask() {

}

void CopyTask::SetId(int id) {
    mId = id;
}

int CopyTask::GetId() const {
    return mId;
}

void CopyTask::run() {
    running = true;
    for
}


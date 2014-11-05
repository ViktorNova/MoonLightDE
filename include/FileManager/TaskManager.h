/*
 * Copyright (C) 2014 Moonlight Desktop Environment Team
 *  Authors:
 *      Alexis López Zubieta <azubieta@uci.cu>
 * 
 * This file is part of Moonlight Desktop Environment.
 *
 * Moonlight Desktop Environment is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight Desktop Environment is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight Desktop Environment. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TASKMANAGER_H
#define	TASKMANAGER_H

#include "Task.h"


#include <QHash>
#include <QString>

namespace FileManager {
    class Worker;

    class TaskManager {
    private:
        QHash<QString, FileManager::Worker*> workers;

    public:
//        FileManager::TasksModel* GetTasksModel();

        TaskManager();
        ~TaskManager();
        
        void Perform(FileManager::Task* task);

        void Perform(FileManager::Task* task, QString worker);
    };
}

#endif	/* TASKMANAGER_H */
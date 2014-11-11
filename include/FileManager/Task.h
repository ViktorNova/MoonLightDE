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

#ifndef TASK_H
#define	TASK_H

#include <QObject>
#include <QString>

namespace FileManager {

    class Task {
        friend class Worker;
    public:
        virtual int GetId() const = 0;
        virtual QString GetDescription() = 0;
        virtual bool IsRunning() = 0;

    public slots:
        virtual void Stop() = 0;

        virtual void Start() = 0;

    signals:
        void started();
        void stopped();


    protected:
        virtual void SetId(int) = 0;

    };

}
Q_DECLARE_INTERFACE(FileManager::Task, "org.moonlightde.FileManager.Task")
#endif	/* TASK_H */
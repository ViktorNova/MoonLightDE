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

#include <QRunnable>

namespace FileManager {

    class Task : public QRunnable {
        friend class Worker;
    public:
        virtual int GetId() const = 0;

        virtual void Cancel() = 0;

        virtual bool IsCanceled() = 0;

        virtual bool IsFinished() = 0;

        virtual bool IsPaused() = 0;

        virtual bool IsRunning() = 0;

        virtual bool IsStarted() = 0;

        virtual void Pause() = 0;

        virtual int ProgressMaximun() = 0;

        virtual int ProgressMinimun() = 0;

        virtual QString ProgressText() = 0;

        virtual QString ProgressRatio() = 0;

        virtual int ProgressValue() = 0;

        virtual void Resume() = 0;

        virtual void run() = 0;

        virtual void SetPaused(int bool_pause) = 0;

        virtual void TogglePaused() = 0;

        virtual void WaitForFinished() = 0;

    protected:
        virtual void SetId(int) = 0;

    };
}

#endif	/* TASK_H */
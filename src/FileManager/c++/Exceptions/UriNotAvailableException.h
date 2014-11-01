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

#ifndef URINOTAVAILABLEEXCEPTION_H
#define	URINOTAVAILABLEEXCEPTION_H

#include <QException>
#include <QString>

class UriNotAvailableException : public QException {
public:

    enum Reason {
        FSNOTAVAILABLE,
        NOREADALLOWED,
        UNKNOWN
    };

    UriNotAvailableException(Reason reason) {
        mReason = reason;
    }

    void raise() const {
        throw *this;
    }

    UriNotAvailableException *clone() const {
        return new UriNotAvailableException(*this);
    }

    const QString GetMsg() const {
        QString msg = "Sorry, was impossible to fetch the requested path. ";
        switch (mReason) {
            case FSNOTAVAILABLE:
                msg += "Due it's not available.";
                break;
            case NOREADALLOWED:
                msg += "You don't have read permissons.";
                break;
            case UNKNOWN:
                msg += "Due an unknown reason.";
                break;
        }
        return msg;
    }

    Reason getMReason() const {
        return mReason;
    }

private:
    Reason mReason;
};

#endif	/* URINOTAVAILABLEEXCEPTION_H */


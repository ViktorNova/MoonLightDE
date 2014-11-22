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

#include "FileSystemServiceImpl.h"

FileSystemServiceImpl::FileSystemServiceImpl(QObject * parent) {
    setParent(parent);
}

FileSystemServiceImpl::~FileSystemServiceImpl() {
}

void FileSystemServiceImpl::setIconProvider(QFileIconProvider* provider) {
    m_Provider = provider;
}

QFileIconProvider* FileSystemServiceImpl::iconProvider() const {
    return m_Provider;
}

QDir FileSystemServiceImpl::dir(const QModelIndex& index) const {
    throw "Not implementet yet.";
}

QFile* FileSystemServiceImpl::file(const QModelIndex& index) const {
    throw "Not implementet yet.";
}

QFileInfo FileSystemServiceImpl::fileInfo(const QModelIndex& index) const {
    throw "Not implementet yet.";
}

QModelIndex FileSystemServiceImpl::index(const QString& path) {
    throw "Not implementet yet.";
}

QModelIndex FileSystemServiceImpl::index(const QString& path, const QVariant& data) {
    throw "Not implementet yet.";
}
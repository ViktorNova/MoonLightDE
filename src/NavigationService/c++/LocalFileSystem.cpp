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

#include "LocalFileSystem.h"

#include <QDir>
#include <QFile>

LocalFileSystem::LocalFileSystem() {
    m_Model.setRootPath("/");
}

LocalFileSystem::~LocalFileSystem() {
}

QAbstractItemModel* LocalFileSystem::effectiveModel() {
    return &m_Model;
}


QModelIndex LocalFileSystem::index(int row, int column, const QModelIndex& parent) const {
    return m_Model.index(row, column, parent);
}

QModelIndex LocalFileSystem::index(const QString& path) {
    return m_Model.index(path, 0);
}

QModelIndex LocalFileSystem::index(const QString& path, const QVariant& data) {
    //FIX: Additional data passed is being  ignored.
    return m_Model.index(path, 0);
}

QVariant LocalFileSystem::data(const QModelIndex& index, int role) const {
    return m_Model.data(index, role);
}

Qt::ItemFlags LocalFileSystem::flags(const QModelIndex& index) const {
    return m_Model.flags(index);
}

QVariant LocalFileSystem::headerData(int section, Qt::Orientation orientation, int role) const {
    return m_Model.headerData(section, orientation, role);
}

QModelIndex LocalFileSystem::parent(const QModelIndex& child) const {
    return m_Model.parent(child);
}

int LocalFileSystem::rowCount(const QModelIndex& parent) const {
    return m_Model.rowCount(parent);
}

int LocalFileSystem::columnCount(const QModelIndex& parent) const {
    return m_Model.columnCount(parent);
}

bool LocalFileSystem::setData(const QModelIndex& index, const QVariant& value, int role) {
    return m_Model.setData(index, value, role);
}

QString LocalFileSystem::path(const QModelIndex& index) const {
    return m_Model.filePath(index);
}

const QString LocalFileSystem::localPath(const QModelIndex& index) {
    return m_Model.filePath(index);
}

QFileInfo LocalFileSystem::fileInfo(const QModelIndex& index) const {
    return m_Model.fileInfo(index);
}

QFile* LocalFileSystem::file(const QModelIndex& index) const {
    QFileInfo inf = m_Model.fileInfo(index);
    return new QFile(inf.path());
}

QDir LocalFileSystem::dir(const QModelIndex& index) const {
    QFileInfo inf = m_Model.fileInfo(index);
    return QDir(inf.path());
}



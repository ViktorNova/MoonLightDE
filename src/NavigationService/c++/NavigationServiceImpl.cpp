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
#include "NavigationServiceImpl.h"

#include <usGetModuleContext.h>
#include <usModuleContext.h>
#include <usAny.h>

#include <QList>

NavigationServiceImpl::NavigationServiceImpl() {
    us::ModuleContext * context = us::GetModuleContext();

    auto refs = context->GetServiceReferences<IItemModelService>("");

    for (auto &ref : refs) {
        IItemModelService * itemModel = context->GetService(ref);
        addModel(ref, itemModel);
    }
}

NavigationServiceImpl::~NavigationServiceImpl() {
}

IItemModelService* NavigationServiceImpl::root() {
    m_Lock.lockForRead();
    IItemModelService* service = m_ItemModels.at(m_Root);
    m_Lock.unlock();
    return service;

}

IItemModelService* NavigationServiceImpl::model(const QString& scheme) {
    m_Lock.lockForRead();
    IItemModelService* service = NULL;
    for (auto &kv : m_ItemModels) {
        us::Any propSchemes = kv.first.GetProperty("schemes");
        if (!propSchemes.Empty()) {
            std::string schemes = propSchemes.ToString();

            if (schemes.find(scheme.toStdString()) != schemes.npos) {
                service = kv.second;
                break;
            }
        }
    }
    m_Lock.unlock();
    return service;
}

std::size_t NavigationServiceImpl::addModel(const us::ServiceReference<IItemModelService>& ref, IItemModelService* service) {
    m_Lock.lockForWrite();

    us::Any prop = ref.GetProperty("role");
    if (!prop.Empty()) {
        std::string role = prop.ToString();

        if (role.find("root") != role.npos)
            m_Root = ref;
    }

    m_ItemModels.insert(std::make_pair(ref, service));
    m_Lock.unlock();
    return m_ItemModels.size();
}

std::size_t NavigationServiceImpl::removeModel(const us::ServiceReference<IItemModelService>& ref) {
    m_Lock.lockForWrite();
    m_ItemModels.erase(ref);
    m_Lock.unlock();
    return m_ItemModels.size();
}


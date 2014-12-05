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

#ifndef NAVIGATIONSERVICEIMPL_H
#define	NAVIGATIONSERVICEIMPL_H

#include <NavigationService/INavigationService.h>
#include <NavigationService/IItemModelService.h>

#include <usServiceTracker.h>
#include <QReadWriteLock>

using namespace NavigationService;

class NavigationServiceImpl : public INavigationService {
public:
    NavigationServiceImpl();
    virtual ~NavigationServiceImpl();

    virtual IItemModelService* model(const QString& scheme);

    virtual IItemModelService* root();

    std::size_t addModel(const us::ServiceReference<IItemModelService> &ref, IItemModelService * service);
    std::size_t removeModel(const us::ServiceReference<IItemModelService> &ref);


private:
    QReadWriteLock m_Lock;
    std::map<us::ServiceReference<IItemModelService>, IItemModelService *> m_ItemModels;
    us::ServiceReference<IItemModelService> m_Root;
};

#endif	/* NAVIGATIONSERVICEIMPL_H */


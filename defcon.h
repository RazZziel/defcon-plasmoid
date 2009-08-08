/***********************************************************************************
* Adjustable Clock: DEFCON level indicator for your KDE desktop.
* Copyright (C) 2009 Ismael Barros (RazZziel) <razielmine@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
***********************************************************************************/

#ifndef DEFCON_H
#define DEFCON_H

#include "ui_config.h"

#include <KIcon>
#include <Plasma/Applet>

#include <Plasma/Svg>
#include <Plasma/DataEngine>
#include <QPainter>
#include <QSizeF>

#include <plasma/svg.h>
#include <plasma/theme.h>

#include <KConfigDialog>
#include <KConfigGroup>

#define DEFAULT_COMMAND  "echo $((RANDOM%5+1))"
#define DEFAULT_INTERVAL 1

class PlasmaDefcon : public Plasma::Applet
{
    Q_OBJECT
    public:
    PlasmaDefcon(QObject *parent, const QVariantList &args);
    ~PlasmaDefcon();

    void paintInterface(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        const QRect& contentsRect);
    void init();
    void createConfigurationInterface(KConfigDialog *parent);
    void loadConfig();

public slots:
    void dataUpdated(const QString& source,
                     const Plasma::DataEngine::Data &data);
    void updateConfig();

private:
    Plasma::Svg m_svg;
    int m_level;
    int m_pollingInterval;
    QString m_command;
    Plasma::DataEngine *m_engine;
    Ui::config m_configUi;
};

K_EXPORT_PLASMA_APPLET(defcon, PlasmaDefcon)
#endif

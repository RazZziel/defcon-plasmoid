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

#include "defcon.h"
#include <QtDebug>

PlasmaDefcon::PlasmaDefcon(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_svg(this),
      m_level(5),
      m_engine(dataEngine("executable"))
{
    m_svg.setImagePath("widgets/defcon");
    setBackgroundHints(DefaultBackground);
    setHasConfigurationInterface(true);
    // setAspectRatioMode(Plasma::ConstrainedSquare);
    resize(300, 600);
}


PlasmaDefcon::~PlasmaDefcon()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

void PlasmaDefcon::init()
{
    KConfigGroup configuration = config();

    loadConfig();
}

void PlasmaDefcon::dataUpdated(const QString& source,
                               const Plasma::DataEngine::Data &data)
{
    qDebug() << source << "=>" << data;

    bool ok;
    int level = data["stdout"].toString().trimmed().toInt( &ok );

    if (ok)
    {        
        m_level = level;
    }

    update();
}

void PlasmaDefcon::paintInterface(QPainter *p,
                                  const QStyleOptionGraphicsItem *option,
                                  const QRect &contentsRect)
{
    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    m_svg.resize( contentsRect.size() );
    QPointF zero = m_svg.elementRect("g2439").topLeft() - contentsRect.topLeft();

    m_svg.paint(p, contentsRect, "g2439");

    switch( m_level )
    {
    case 1:
        m_svg.paint(p, m_svg.elementRect("rect2240").translated(-zero), "path3306");
        break;
    case 2:
        m_svg.paint(p, m_svg.elementRect("rect3217").translated(-zero), "path3308");
        break;
    case 3:
        m_svg.paint(p, m_svg.elementRect("rect3219").translated(-zero), "path3310");
        break;
    case 4:
        m_svg.paint(p, m_svg.elementRect("rect3221").translated(-zero), "path3314");
        break;
    case 5:
        m_svg.paint(p, m_svg.elementRect("rect3225").translated(-zero), "path3312");
        break;
    }

    p->save();
    p->setPen(Qt::white);
    p->restore();
}

void PlasmaDefcon::createConfigurationInterface(KConfigDialog *parent)
{
    KConfigGroup configuration = config();

    QWidget *config_dialog = new QWidget;
    m_configUi.setupUi(config_dialog);

    m_configUi.command->setText( m_command );
    m_configUi.pollingInterval->setValue( m_pollingInterval );

    parent->addPage(config_dialog, "General", "preferences-other");

    connect(parent, SIGNAL( okClicked() ), this, SLOT( updateConfig() ));
}

void PlasmaDefcon::loadConfig()
{
    KConfigGroup configuration = config();

    m_command = configuration.readEntry("command", DEFAULT_COMMAND);
    m_pollingInterval = configuration.readEntry("pollingInterval", DEFAULT_INTERVAL);

    m_engine->connectSource( m_command, this, m_pollingInterval*1000 );
}

void PlasmaDefcon::updateConfig()
{
    KConfigGroup configuration = config();

    m_engine->disconnectSource( m_command, this );

    m_command = m_configUi.command->text().trimmed();
    m_pollingInterval = m_configUi.pollingInterval->value();

    if (m_command.length() == 0)
    {
        m_command = DEFAULT_COMMAND;
    }
    if (m_pollingInterval == 0)
    {
        m_pollingInterval = DEFAULT_INTERVAL;
    }

    m_engine->connectSource( m_command, this, m_pollingInterval*1000 );

    configuration.writeEntry("command", m_command);
    configuration.writeEntry("pollingInterval", m_pollingInterval);

    emit configNeedsSaving();
}


#include "defcon.moc"

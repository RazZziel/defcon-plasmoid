#ifndef DEFCON_H
#define DEFCON_H

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

// Define our plasma Applet
class PlasmaDefcon : public Plasma::Applet
{
    Q_OBJECT
    public:
    // Basic Create/Destroy
    PlasmaDefcon(QObject *parent, const QVariantList &args);
    ~PlasmaDefcon();

    // The paintInterface procedure paints the applet to screen
    void paintInterface(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        const QRect& contentsRect);
    void init();
    void createConfigurationInterface(KConfigDialog *parent);
    void loadConfig();
    void saveConfig();

public slots:
    void dataUpdated(const QString& source,
                     const Plasma::DataEngine::Data &data);

private:
    Plasma::Svg m_svg;
    int m_level;
    void connectToEngine();
};

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(defcon, PlasmaDefcon)
#endif

#include "defcon.h"
#include <QtDebug>

PlasmaDefcon::PlasmaDefcon(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_svg(this),
      m_level(5)
{
    m_svg.setImagePath("widgets/defcon");
    setBackgroundHints(DefaultBackground);
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
    loadConfig();
    connectToEngine();
}

void PlasmaDefcon::connectToEngine()
{
    Plasma::DataEngine *engine = dataEngine("executable");
    engine->connectSource( "echo $((RANDOM%5+1))", this, 1000 );
}

void PlasmaDefcon::dataUpdated(const QString& source,
                               const Plasma::DataEngine::Data &data)
{
    qDebug() << data;

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
    // appearance_dialog = new AppearanceDialog();
    // appearance_dialog->checkTrayIconSize->setChecked(cfg_tray_icon_size);
    // appearance_dialog->selFontFamily->setCurrentFont(cfg_font);

    // config_dialog = new ConfigDialog();
    // config_dialog->loadAccounts(accounts);

    // parent->addPage(appearance_dialog, tr2i18n("Appearance"), "preferences-desktop-theme");
    // parent->addPage(config_dialog, tr2i18n("Accounts"), "mail-message");

    // connect(parent, SIGNAL( okClicked() ), this, SLOT( saveConfig() ));
    // connect(parent, SIGNAL( finished() ), this, SLOT( startMailCheckers() ));
}

void PlasmaDefcon::loadConfig()
{
    // KConfigGroup cfg = config();

    // cfg_tray_icon_size = cfg.readEntry("tray_icon_size", false);
    // cfg_font.setFamily(cfg.readEntry("font_family", font().family()));

    // KConfigGroup cfg_accounts(&cfg, "Accounts");

    // QStringList account_ids = cfg_accounts.groupList();
    // account_ids.sort();

    // for (int i = 0; i < account_ids.count(); ++i) {
    //     Account * account = new Account(new KConfigGroup(&cfg_accounts, account_ids.value(i)));

    //     if (account->name.isEmpty()) delete account;
    //     else accounts.push_back(account);
    // }
}

void PlasmaDefcon::saveConfig()
{
    // KConfigGroup cfg = config();

    // cfg_tray_icon_size = appearance_dialog->checkTrayIconSize->isChecked();
    // cfg.writeEntry("tray_icon_size", cfg_tray_icon_size);
    // cfg_font.setFamily(appearance_dialog->selFontFamily->currentFont().family());
    // cfg.writeEntry("font_family", cfg_font.family());

    // KConfigGroup cfg_accounts(&cfg, "Accounts");
    // cfg_accounts.deleteGroup();

    // dropAccounts();

    // for (int i = 0; i < config_dialog->listAccounts->count(); ++i) {
    //     KConfigGroup cfg_account(&cfg_accounts, QString::number(i));
    //     Account * account = new Account(((ListAccountItem *) config_dialog->listAccounts->item(i))->account);
    //     account->saveConfiguration(&cfg_account);
    //     accounts.push_back(account);
    // }

    // cfg.sync();

    // createMailCheckers();
    // messages_dialog->createAccountItems(mail_checkers);

    // update();
}


#include "defcon.moc"

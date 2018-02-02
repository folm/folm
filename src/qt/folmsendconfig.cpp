#include "folmsendconfig.h"
#include "ui_folmsendconfig.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "init.h"
#include "optionsmodel.h"
#include "walletmodel.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>

FolmsendConfig::FolmsendConfig(QWidget* parent) : QDialog(parent),
                                                        ui(new Ui::FolmsendConfig),
                                                        model(0)
{
    ui->setupUi(this);

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

FolmsendConfig::~FolmsendConfig()
{
    delete ui;
}

void FolmsendConfig::setModel(WalletModel* model)
{
    this->model = model;
}

void FolmsendConfig::clickBasic()
{
    configure(true, 1000, 2);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Folmsend Configuration"),
        tr(
            "Folmsend was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening FOLM's configuration screen.")
            .arg(strAmount));

    close();
}

void FolmsendConfig::clickHigh()
{
    configure(true, 1000, 8);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Folmsend Configuration"),
        tr(
            "Folmsend was successfully set to high (%1 and 8 rounds). You can change this at any time by opening FOLM's configuration screen.")
            .arg(strAmount));

    close();
}

void FolmsendConfig::clickMax()
{
    configure(true, 1000, 16);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("Folmsend Configuration"),
        tr(
            "Folmsend was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening FOLM's configuration screen.")
            .arg(strAmount));

    close();
}

void FolmsendConfig::configure(bool enabled, int coins, int rounds)
{
    QSettings settings;

    settings.setValue("nFolmsendRounds", rounds);
    settings.setValue("nAnonymizeFolmAmount", coins);

    nFolmsendRounds = rounds;
    nAnonymizeFolmAmount = coins;
}

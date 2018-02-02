#ifndef OBFUSCATIONCONFIG_H
#define OBFUSCATIONCONFIG_H

#include <QDialog>

namespace Ui
{
class FolmsendConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class FolmsendConfig : public QDialog
{
    Q_OBJECT

public:
    FolmsendConfig(QWidget* parent = 0);
    ~FolmsendConfig();

    void setModel(WalletModel* model);


private:
    Ui::FolmsendConfig* ui;
    WalletModel* model;
    void configure(bool enabled, int coins, int rounds);

private slots:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // OBFUSCATIONCONFIG_H

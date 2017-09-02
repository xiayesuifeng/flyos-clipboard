//
// Created by linux on 17-8-30.
//

#include "ExitDialog.h"
#include <QPushButton>

#include <QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFrame>
#include <QtCore/QStandardPaths>
#include <QtCore/QSettings>

#include <QDebug>
#include <QtCore/QFile>

ExitDialog::ExitDialog(QWidget *parent) :
        DDialog("自动启动剪切板?","是否在启动时自动启动剪切板",parent) {

    checkBox = new QCheckBox("不再提示", this);

    QPushButton *startBuuton = new QPushButton("启动", this);
    QPushButton *noStartBuuton = new QPushButton("不启动", this);

    QFrame *mainFrame = new QFrame(this);

    QHBoxLayout *mainLayout = new QHBoxLayout(mainFrame);

    mainLayout->addWidget(checkBox);
    mainLayout->addStretch();
    mainLayout->addWidget(startBuuton);
    mainLayout->addWidget(noStartBuuton);

    this->addContent(mainFrame);

    startBuuton->setFocus();

    QString confPath = (QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first());

    configPath = confPath
                 + "/" + QApplication::organizationName()
                 + "/" + QApplication::applicationName()
                 + "/" + QApplication::applicationName()
                 + ".conf";

    autoPath = confPath;
    autoPath += "/autostart/flyos-clipboard.desktop";

    connect(startBuuton, &QPushButton::clicked, this, &ExitDialog::startClick);

    connect(noStartBuuton, &QPushButton::clicked, this, &ExitDialog::noStartClick);
}

void ExitDialog::done(int i) {
    noAgentTip(checkBox->isChecked());
    QDialog::done(i);
}

void ExitDialog::noAgentTip(bool Status) {
    QSettings conf(configPath, QSettings::IniFormat);
    conf.setValue("setting/tipDialog", !Status);
}

void ExitDialog::startClick() {
    QSettings conf(configPath, QSettings::IniFormat);

    if (QFile::exists("/usr/local/share/applications/flyos-clipboard.desktop"))
        QFile::copy("/usr/local/share/applications/flyos-clipboard.desktop", autoPath);
    else
        QFile::copy("/usr/share/applications/flyos-clipboard.desktop", autoPath);

    conf.setValue("setting/autoStart", true);

    done(1);
}

void ExitDialog::noStartClick() {
    done(2);
}

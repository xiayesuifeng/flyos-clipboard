//
// Created by linux on 17-8-24.
//

#include "mainwindow.h"
#include "base/fileUtil.h"
#include <QApplication>
#include <QtGui/QClipboard>
#include <DApplication>
#include <QDesktopWidget>

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMessageBox>

#include <QDebug>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>

mainwindow::mainwindow(QWidget *parent) :
        DBlurEffectWidget(parent),
        clipboard(QApplication::clipboard()) {

    this->setFixedSize(350, 500);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    this->setMaskColor(DBlurEffectWidget::LightColor);

    trayIcon = new QSystemTrayIcon;
    trayIcon->setToolTip("剪切板");
    trayIcon->setIcon(QIcon(":/images/clipboard.svg"));
    trayIcon->show();

    QMenu *menu = new QMenu;

    mainAction = new QAction("主窗口");
    aboutAction = new QAction("关于");
    exitAction = new QAction("退出");

    menu->addAction(mainAction);
    menu->addSeparator();
    menu->addAction(aboutAction);
    menu->addAction(exitAction);

    trayIcon->setContextMenu(menu);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout(this);

    title = new QLabel("共有0条历史", this);

    clearAllButton = new QPushButton(this);
    clearAllButton->setFixedSize(16, 16);
    clearAllButton->setStyleSheet(ReadFile(":/styles/clearAllButton.css"));

    QPushButton *settings = new QPushButton(this);
    settings->setFixedSize(18, 18);
    settings->setStyleSheet(ReadFile(":/styles/settingsButton.css"));
    settings->setMenu(menu);

    topLayout->setMargin(10);
    topLayout->setSpacing(10);
    topLayout->addWidget(title, 1, Qt::AlignCenter | Qt::AlignLeft);
    topLayout->addWidget(clearAllButton, 0, Qt::AlignRight);
    topLayout->addWidget(settings, 0, Qt::AlignRight);

    listWidget = new ListWidget(this);

    mainLayout->setMargin(0);
    mainLayout->addLayout(topLayout, 0);
    mainLayout->addWidget(listWidget, 1);

    setLayout(mainLayout);

    initConnect();
}


void mainwindow::initConnect() {
    connect(mainAction, &QAction::triggered, this, [=] {
        this->show();
    });

    connect(aboutAction, &QAction::triggered, this, [=] {

    });

    connect(exitAction, &QAction::triggered, this, &mainwindow::close);

    connect(clipboard, &QClipboard::dataChanged, this, &mainwindow::clipboardDataChanged);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &mainwindow::trayIconActivated);

    connect(clearAllButton, &QPushButton::clicked, this, &mainwindow::clearAllButtonClick);

    connect(listWidget, &ListWidget::countChange, this, &mainwindow::countChange);
}


void mainwindow::clipboardDataChanged() {
    QString text = clipboard->text();
    if (!text.isEmpty())
        listWidget->addItem(text);
}

void mainwindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::ActivationReason::Trigger)
        this->show();
}

void mainwindow::showEvent(QShowEvent *event) {
    DBlurEffectWidget::showEvent(event);
    QSize size = qApp->desktop()->size();
    QRect rect = trayIcon->geometry();
    int x, y;
    if ((size.height() - rect.y()) < this->height()) {
        x = rect.x() - this->height();
    } else {
        x = rect.x();
    }

    if ((size.width() - rect.x()) < this->width()) {
        y = rect.y() - this->width();
    } else {
        y = rect.y();
    }

    this->move(x, y);
}

bool mainwindow::event(QEvent *event) {
#ifndef QT_DEBUG
    if (event->type() == event->WindowDeactivate)
        this->hide();
#endif
    return QWidget::event(event);
}

void mainwindow::clearAllButtonClick() {
    listWidget->clear();
}

void mainwindow::countChange(int count) {
    title->setText(tr("共有%1条历史").arg(count));
}

void mainwindow::closeEvent(QCloseEvent *event) {
    QWidget::closeEvent(event);
    QString confPath = (QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first());
    QString autoPath = confPath;
    autoPath += "/autostart/flyos-clipboard.desktop";

    QString configPath = tr("%1/%2/%3/%4.conf")
            .arg(configPath)
            .arg(QApplication::organizationName())
            .arg(QApplication::applicationName())
            .arg(QApplication::applicationName());

    QSettings conf(configPath, QSettings::IniFormat);
    if (!conf.value("setting/autoStart", false).toBool()) {
        if (QMessageBox::information(this, "自动启动剪切板?", "是否在启动时自动启动剪切板", "取消", "不启动", "启动", 2) == 2) {
            if (QFile::exists("/usr/local/share/applications/flyos-clipboard.desktop"))
                QFile::copy("/usr/local/share/applications/flyos-clipboard.desktop", autoPath);
            else
                QFile::copy("/usr/share/applications/flyos-clipboard.desktop", autoPath);

            conf.setValue("setting/autoStart", true);
        }
    }

}
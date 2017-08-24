//
// Created by linux on 17-8-24.
//

#include "mainwindow.h"
#include <QApplication>
#include <QtGui/QClipboard>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSystemTrayIcon>
#include <DApplication>
#include <QDesktopWidget>

#include <QDebug>

mainwindow::mainwindow(QWidget *parent) :
        DBlurEffectWidget(parent),
        clipboard(QApplication::clipboard()) {

    this->setFixedSize(350, 500);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setGeometry(0, 30, 350, 470);
    this->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    this->setMaskColor(DBlurEffectWidget::LightColor);

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon;
    trayIcon->setToolTip("剪切板");
    trayIcon->setIcon(QIcon(":/images/clipboard.png"));
    trayIcon->show();

    QMenu *menu = new QMenu;

    QAction *mainAction = new QAction("主窗口");
    QAction *aboutAction = new QAction("关于");
    QAction *exitAction = new QAction("退出");

    menu->addAction(mainAction);
    menu->addAction(aboutAction);
    menu->addAction(exitAction);

    connect(mainAction, &QAction::triggered, this, [=] {
        QSize size = qApp->desktop()->size();
        QRect rect = trayIcon->geometry();
        this->show();
    });
    connect(aboutAction, &QAction::triggered, this, [=] {
        DAboutDialog *dialog = qApp->aboutDialog();
        qDebug() << dialog;

    });
    connect(exitAction, &QAction::triggered, this, [=] {
        qApp->exit(0);
    });

    trayIcon->setContextMenu(menu);

    QListWidget *listWidget = new QListWidget(this);

    listWidget->setGeometry(0, 30, 350, 470);

    connect(clipboard, &QClipboard::dataChanged, this, [=] {
        listWidget->addItem(clipboard->text());
    });
}

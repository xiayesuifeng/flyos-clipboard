//
// Created by linux on 17-8-24.
//

#include "mainwindow.h"
#include <QApplication>
#include <QtGui/QClipboard>
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

    trayIcon = new QSystemTrayIcon;
    trayIcon->setToolTip("剪切板");
    trayIcon->setIcon(QIcon(":/images/clipboard.png"));
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

    listWidget = new QListWidget(this);

    listWidget->setGeometry(0, 30, 350, 470);

    initConnect();
}


void mainwindow::initConnect() {
    connect(mainAction, &QAction::triggered, this, [=] {
        QSize size = qApp->desktop()->size();
        QRect rect = trayIcon->geometry();
        this->show();
    });

    connect(aboutAction, &QAction::triggered, this, [=] {

    });

    connect(exitAction, &QAction::triggered, this, &mainwindow::close);

    connect(clipboard, &QClipboard::dataChanged, this, &mainwindow::clipboardDataChanged);
}

void mainwindow::clipboardDataChanged() {
    listWidget->addItem(clipboard->text());
}
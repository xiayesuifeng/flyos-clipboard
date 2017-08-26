//
// Created by linux on 17-8-24.
//

#include "mainwindow.h"
#include "base/fileUtil.h"
#include <QApplication>
#include <QtGui/QClipboard>
#include <DApplication>
#include <QDesktopWidget>

#include <QDebug>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

mainwindow::mainwindow(QWidget *parent) :
        DBlurEffectWidget(parent),
        clipboard(QApplication::clipboard()) {

    this->setFixedSize(350, 500);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

//    this->setGeometry(0, 30, 350, 470);
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

    QPushButton *settings = new QPushButton(this);
    settings->setFixedSize(20, 20);
    settings->setStyleSheet(ReadFile(":/styles/settingsButton.css"));

    topLayout->setMargin(10);
    topLayout->addWidget(title, 1, Qt::AlignCenter | Qt::AlignLeft);
    topLayout->addWidget(settings, 0, Qt::AlignRight);

    listWidget = new ListWidget(this);

    mainLayout->setMargin(0);
    mainLayout->addLayout(topLayout,0);
    mainLayout->addWidget(listWidget,1);

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
}


void mainwindow::clipboardDataChanged() {
    QString text = clipboard->text();
    if (!text.isEmpty())
        listWidget->addItem(text);

    count++;
    title->setText(tr("共有%1条历史").arg(count));
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

void mainwindow::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    this->hide();
}


//
// Created by linux on 17-8-25.
//

#include <QtWidgets/QPushButton>
#include <QApplication>
#include <QClipboard>

#include "ListItem.h"
#include "../base/fileUtil.h"

ListItem::ListItem(QString text, QWidget *parent) :
        QFrame(parent){
    this->setFixedSize(320,50);
    this->setStyleSheet(ReadFile(":/styles/listItem.css"));

    label = new QLabel(this);
    label->setFixedSize(300, 30);
    label->setText(text);
    QStringList list = text.split("\n");
    if (list.count() >=2){
        this->setFixedHeight(80);
        label->setFixedSize(300, 60);
    }

    label->move(10, 10);

    QPushButton *copyButton = new QPushButton(this);
    copyButton->setGeometry(305 - 6 -16 -6, 6, 16, 16);
    copyButton->setStyleSheet(ReadFile(":/styles/copyButton.css"));

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setGeometry(305 - 6, 6, 16, 16);
    closeButton->setStyleSheet(ReadFile(":/styles/closeButton.css"));

    connect(copyButton, &QPushButton::clicked, this, &ListItem::copyButtonClick);
    connect(closeButton, &QPushButton::clicked, this, &ListItem::closeButtonClick);
}


void ListItem::copyButtonClick() {
    qApp->clipboard()->setText(label->text());
}

void ListItem::closeButtonClick() {
    emit removeItem(this);
}


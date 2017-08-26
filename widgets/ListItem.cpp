//
// Created by linux on 17-8-25.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "ListItem.h"
#include "../base/fileUtil.h"

ListItem::ListItem(QString text, QWidget *parent) :
        QFrame(parent){
    this->setFixedSize(320,50);
    this->setStyleSheet(ReadFile(":/styles/listItem.css"));

    QLabel *label = new QLabel(this);
    label->setFixedSize(300, 30);
    label->setText(text);
    QStringList list = text.split("\n");
    if (list.count() >=2){
        this->setFixedHeight(80);
        label->setFixedSize(300, 60);
    }

    label->move(10, 10);

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setGeometry(290, 10, 20, 20);
    closeButton->setStyleSheet(ReadFile(":/styles/closeButton.css"));

    connect(closeButton, &QPushButton::clicked, this, &ListItem::closeButtonClick);
}

void ListItem::closeButtonClick() {
    emit removeItem(this);
}

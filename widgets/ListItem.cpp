//
// Created by linux on 17-8-25.
//

#include <QtWidgets/QLabel>
#include "ListItem.h"

ListItem::ListItem(QString text, QWidget *parent) :
        QFrame(parent){
    this->setFixedHeight(30);
    QLabel *label = new QLabel(this);
    label->setFixedSize(300, 20);
    label->setText(text);
    if (label->fontMetrics().height() > 30 ){
        this->setFixedHeight(50);
        label->setFixedSize(300, 40);
    }

    label->move(5, 5);
}

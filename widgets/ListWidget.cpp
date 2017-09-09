//
// Created by linux on 17-8-25.
//

#include <QtWidgets/QVBoxLayout>
#include "ListWidget.h"

#include <QDebug>

ListWidget::ListWidget(QWidget *parent) :
        QScrollArea(parent) {

    QFrame *mainFrame = new QFrame(this);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->setSpacing(10);
    mainFrame->setLayout(mainLayout);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setWidgetResizable(true);
    this->setStyleSheet("background:transparent");
    this->setWidget(mainFrame);

}

void ListWidget::addItem(QString text) {
    if (isCopy){
        isCopy = false;
        return;
    }
    ListItem *item = new ListItem(text, this);

    mainLayout->insertWidget(0, item, 0);

    connect(item, &ListItem::removeItem, this, &ListWidget::removeItem);
    connect(item, &ListItem::setIsCopy, this, &ListWidget::setIsCopy);

    emit countChange(mainLayout->count() - 1);
}

void ListWidget::removeItem(ListItem *item) {
    item->setParent(nullptr);
    mainLayout->removeWidget(item);
    delete item;
    emit countChange(mainLayout->count() - 1);
}

void ListWidget::clear() {
    QLayoutItem *item;
    while (mainLayout->count() > 1){
        if ((item = mainLayout->itemAt(0)) != nullptr) {
            QWidget *widget = item->widget();
            if (widget != nullptr) {
                widget->setParent(nullptr);
                mainLayout->removeWidget(widget);
                delete widget;
            }
        }
    }
    emit countChange(mainLayout->count() - 1);
}

void ListWidget::setIsCopy(bool isCopy) {
    ListWidget::isCopy = isCopy;
}

//
// Created by linux on 17-8-25.
//

#include <QtWidgets/QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QtWidgets/QHBoxLayout>

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

    toolFrame = new QFrame(this);
    toolFrame->setVisible(false);
    toolFrame->setGeometry(0, 0, 320, 22);
    QHBoxLayout *toolLayout = new QHBoxLayout(toolFrame);
    toolLayout->setMargin(6);
    toolLayout->setSpacing(6);
    toolLayout->setAlignment(Qt::AlignRight);

    QPushButton *copyButton = new QPushButton(this);
    copyButton->setFixedSize(16, 16);
    copyButton->setStyleSheet(ReadFile(":/styles/copyButton.css"));

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setFixedSize(16, 16);
    closeButton->setStyleSheet(ReadFile(":/styles/closeButton.css"));

    toolLayout->addWidget(copyButton);
    toolLayout->addWidget(closeButton);

    connect(copyButton, &QPushButton::clicked, this, &ListItem::copyButtonClick);
    connect(closeButton, &QPushButton::clicked, this, &ListItem::closeButtonClick);
}


void ListItem::copyButtonClick() {
    emit setIsCopy(true);
    qApp->clipboard()->setText(label->text());
}

void ListItem::closeButtonClick() {
    emit removeItem(this);
}


void ListItem::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    toolFrame->setVisible(true);
}

void ListItem::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    toolFrame->setVisible(false);
}

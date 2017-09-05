//
// Created by linux on 17-9-5.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QApplication>
#include "AboutDialog.h"

#include <QDebug>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(400, 280);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    this->setLayout(mainLayout);

    QLabel *icon = new QLabel(this);

    icon->setPixmap(QPixmap(qApp->property("productrtIcon").toString()).scaled(100, 100));

    QLabel *ProductName = new QLabel(qApp->property("productName").toString(),this);
    QLabel *version = new QLabel("Version:"+qApp->property("version").toString(),this);
    QLabel *description = new QLabel(qApp->property("description").toString(),this);


    mainLayout->addStretch();
    mainLayout->addWidget(icon,0,Qt::AlignCenter);
    mainLayout->addWidget(ProductName,0,Qt::AlignCenter);
    mainLayout->addWidget(version,0,Qt::AlignCenter);
    mainLayout->addWidget(description,0,Qt::AlignCenter);
    mainLayout->addStretch();

}

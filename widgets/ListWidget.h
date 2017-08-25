//
// Created by linux on 17-8-25.
//

#ifndef FLYOS_CLIPBOARD_LISTWIDGET_H
#define FLYOS_CLIPBOARD_LISTWIDGET_H


#include <QtWidgets/QScrollArea>

class ListWidget : public QScrollArea{
    Q_OBJECT
public:
    ListWidget(QWidget *parent = nullptr);

    void addItem(QString text);

private:
    QVBoxLayout *mainLayout;

};


#endif //FLYOS_CLIPBOARD_LISTWIDGET_H

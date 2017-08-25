//
// Created by linux on 17-8-25.
//

#ifndef FLYOS_CLIPBOARD_LISTITEM_H
#define FLYOS_CLIPBOARD_LISTITEM_H


#include <QtWidgets/QFrame>

class ListItem : public QFrame{
    Q_OBJECT
public:
    explicit ListItem(QString text ,QWidget *parent = nullptr);

};


#endif //FLYOS_CLIPBOARD_LISTITEM_H

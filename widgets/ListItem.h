//
// Created by linux on 17-8-25.
//

#ifndef FLYOS_CLIPBOARD_LISTITEM_H
#define FLYOS_CLIPBOARD_LISTITEM_H


#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

class ListItem : public QFrame {
Q_OBJECT
public:
    explicit ListItem(QString text, QWidget *parent = nullptr);

private:
    QLabel *label;

    QFrame *toolFrame;


private slots:

    void copyButtonClick();
    void closeButtonClick();

protected:
    virtual void enterEvent(QEvent *event);

    virtual void leaveEvent(QEvent *event);

private:

signals:

    void removeItem(ListItem *item);

    void setIsCopy(bool isCopy);

};


#endif //FLYOS_CLIPBOARD_LISTITEM_H

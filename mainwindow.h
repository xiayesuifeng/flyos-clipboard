//
// Created by linux on 17-8-24.
//

#ifndef FLYOS_CLIPBOARD_MAINWINDOW_H
#define FLYOS_CLIPBOARD_MAINWINDOW_H


#include <QtWidgets/QDialog>
#include <ddialog.h>
#include <DMainWindow>
#include <DBlurEffectWidget>
#include <QtWidgets/QAction>
#include <QMenu>
#include <DAboutDialog>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QListWidget>
#include "widgets/ListWidget.h"

DWIDGET_USE_NAMESPACE

class mainwindow : public DBlurEffectWidget{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);

private:
    QClipboard *clipboard;
    ListWidget *listWidget;
    QSystemTrayIcon *trayIcon;

    QAction *mainAction;
    QAction *aboutAction;
    QAction *exitAction;

    QPushButton *clearAllButton;

    QLabel *title;

    void initConnect();

private slots:

    void clipboardDataChanged();
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void clearAllButtonClick();

protected:
    virtual void showEvent(QShowEvent *event);

    virtual bool event(QEvent *event);

    void countChange(int count);

};


#endif //FLYOS_CLIPBOARD_MAINWINDOW_H

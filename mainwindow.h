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

DWIDGET_USE_NAMESPACE

class mainwindow : public DBlurEffectWidget{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);

private:
    QClipboard *clipboard;
    QListWidget *listWidget;
    QSystemTrayIcon *trayIcon;

    QAction *mainAction;
    QAction *aboutAction;
    QAction *exitAction;

    void initConnect();

private slots:

    void clipboardDataChanged();
};


#endif //FLYOS_CLIPBOARD_MAINWINDOW_H

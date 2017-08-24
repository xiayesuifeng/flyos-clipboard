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

DWIDGET_USE_NAMESPACE

class mainwindow : public DBlurEffectWidget{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = nullptr);

private:
    QClipboard *clipboard;

};


#endif //FLYOS_CLIPBOARD_MAINWINDOW_H

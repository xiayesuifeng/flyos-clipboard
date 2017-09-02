//
// Created by linux on 17-8-30.
//

#ifndef FLYOS_CLIPBOARD_EXITDIALOG_H
#define FLYOS_CLIPBOARD_EXITDIALOG_H

#include <ddialog.h>
#include <QtWidgets/QCheckBox>

DWIDGET_USE_NAMESPACE

class ExitDialog : public DDialog{
    Q_OBJECT
public:
    explicit ExitDialog(QWidget *parent = nullptr);

    virtual void done(int i);

private:
    QString configPath;

    QString autoPath;


    QCheckBox *checkBox;

    void noAgentTip(bool Status);

private Q_SLOT:

    void startClick();
    void noStartClick();
};


#endif //FLYOS_CLIPBOARD_EXITDIALOG_H

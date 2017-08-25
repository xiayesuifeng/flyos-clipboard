//
// Created by linux on 17-3-31.
//

#include "fileUtil.h"
#include <QDebug>
QString ReadFile(const QString& path) {
    QFile file(path);
    if (file.exists()) {
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "ReadFile() failed to open" << path;
            return "";
        }
        QTextStream text_stream(&file);
        QString str = text_stream.readAll();
        file.close();
        return str;
    } else {
        qWarning() << "ReadFileContent() file not found: " << path;
        return "";
    }
}
#include "mainwindow.h"
#include "ipinputdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString ip;
    QString expectedIp = "10.10.41.252";
    bool validIp = false, cancelBtnClicked = false;

    while (!validIp && !cancelBtnClicked)
    {
        IpInputDialog dialog;
        if (dialog.exec() == QDialog::Accepted)
        {
            ip = dialog.getIpAddress();

            // Checking for proper IP format
            QRegularExpression ipRegex(R"(^((25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)\.){3}(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)$)");
            if ( !ipRegex.match(ip).hasMatch() )
            {
                QMessageBox::warning(nullptr, "Invalid Format", "Please enter a proper IP address.");
                continue;
            }

            // Logic check (authorized IP addresses)
            if (ip != expectedIp)
            {
                QMessageBox::warning(nullptr, "Access Denied", "This IP address is not authorized.");
                continue;
            }

            validIp = true;
        }
        else // if (dialog.exec() == QDialog::Rejected)
        {
            QApplication::quit();
            cancelBtnClicked = true;
        }
    }

    if (cancelBtnClicked)
    {
        qDebug() << "You've hit the Cancel button";
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}

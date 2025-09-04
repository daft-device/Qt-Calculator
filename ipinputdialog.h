#ifndef IPINPUTDIALOG_H
#define IPINPUTDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>

class IpInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IpInputDialog(QWidget* parent = nullptr);

    QString getIpAddress() const;

private:
    QLineEdit* ipEdit;
};

#endif // IPINPUTDIALOG_H

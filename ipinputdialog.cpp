#include "ipinputdialog.h"

IpInputDialog::IpInputDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Connect");



    QLabel* label = new QLabel("Enter IP Address:");
    ipEdit = new QLineEdit();
    ipEdit->setPlaceholderText("e.g. 192.168.1.181");

    QPushButton* okBtn = new QPushButton("OK");
    QPushButton* cancelBtn = new QPushButton("Cancel");

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(ipEdit);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(okBtn, &QPushButton::clicked, this, &IpInputDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &IpInputDialog::reject);
}

QString IpInputDialog::getIpAddress() const
{
    return ipEdit->text();
}

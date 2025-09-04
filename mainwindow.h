#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ipinputdialog.h"

double firstNum;
bool userInputSecondNum = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sets the fixed app width and height
    setFixedSize(302, 361); // Note: Matches what was set in Design Mode for mainwindow.ui

    // Detect what digits are being entered
    connect(ui->pushButton_num0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_num9, SIGNAL(released()), this, SLOT(digit_pressed()));

    // Detect whether using "%" or "+/-" operations
    connect(ui->pushButton_signs, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
    
    // Detect whether using addition | subtraction | multiplication | division
    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operations_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operations_pressed()));

    // Ensuring you can enter a second value
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
    Brief: This function will handle digit entering and various misc issues.
*/
void MainWindow::digit_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    
    double labelNumber = 0;
    QString newLabel;
    
    if ( !userInputSecondNum && 
        (ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() ||
        ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) )
    {
        labelNumber = button->text().toDouble();
        newLabel = QString::number(labelNumber, 'g', 15);
        userInputSecondNum = true;
    }
    else
    {
        // Will allow you to enter "0.0xxxxxx", etc.
        if (ui->display->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->display->text() + button->text();
        }
        else
        {
            labelNumber = (ui->display->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }

    ui->display->setText(newLabel);
}

/*
    Brief: This function will handle using decimal points in your values.
*/
void MainWindow::on_pushButton_float_released()
{
    if (!ui->display->text().contains('.'))
        ui->display->setText(ui->display->text() + ".");
    else
    {
        // Second decimal point will not be entered
    }
}

/*
    Brief: This function will handle whether you're switching a value's signs ||
           converting your current whole number to a percent out of 100.
*/
void MainWindow::unary_operation_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    double labelNumber = ui->display->text().toDouble();
    QString newLabel;

    if (button->text() == "+/-")
    {
        labelNumber *= -1;
    }
    else if (button->text() == "%")
    {
        labelNumber *= 0.01;
    }

    newLabel = QString::number(labelNumber, 'g', 15);
    ui->display->setText(newLabel);
}

/*
    Brief: This function will reset all operations, as if opening app again.
*/
void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);

    userInputSecondNum = false;

    ui->display->setText("0");
}

/*
    Brief: This function will check whether the user is adding ||
           subtracting || multiplying || dividing ONLY 2 values.
*/
void MainWindow::on_pushButton_equals_released()
{
    double labelNumber = 0, secondNum = ui->display->text().toDouble();
    QString newLabel;
    bool divByZero = false;

    if (ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        
        // Set to false to avoid repeated operations, unless specified by user - Vinh Sep 02 2025
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        ui->pushButton_multiply->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        // The following 2 conditions will handle division by zero
        if (secondNum != 0)
            labelNumber = firstNum / secondNum;
        else
        {
            newLabel = QString("Cannot divide by zero.");
            divByZero = true;
        }
        
        ui->pushButton_divide->setChecked(false);
    }
    
    if (!divByZero)
    {
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    
    ui->display->setText(newLabel);

    userInputSecondNum = false;
}

/*
    Brief: This function will handle whether doing addition ||
           subtraction || multiplication || division operations.
*/
void MainWindow::binary_operations_pressed()
{
    QPushButton* button = (QPushButton*)sender();
    
    firstNum = ui->display->text().toDouble();

    button->setChecked(true);
}

/*
    Brief: This function will delete one digit from the current value.
           If the value is only 1 digit, then reset to 0.
*/
void MainWindow::on_pushButton_del_released()
{
    QString currentText = ui->display->text();
    if (!currentText.isEmpty())
    {
        if (currentText.length() > 1)
        {
            currentText.chop(1);
        }
        else if (currentText.length() == 1)
        {
            currentText = QString("0");
        }

        ui->display->setText(currentText);
    }
}

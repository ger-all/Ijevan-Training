#include "mainwindow.h"
#include <QWidget>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Central widget
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Display
    display = new QLineEdit("0", central);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(40);

    // Layouts
    QVBoxLayout* vLayout = new QVBoxLayout(central);
    QGridLayout* gridLayout = new QGridLayout();

    vLayout->addWidget(display);
    vLayout->addLayout(gridLayout);

    // Create digit buttons and add to grid
    int number = 1;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[number] = new QPushButton(QString::number(number), central);
            buttons[number]->setFixedSize(50, 50);
            gridLayout->addWidget(buttons[number], 2-row, col); // arrange like calculator
            connect(buttons[number], &QPushButton::clicked, this, &MainWindow::digitClicked);
            ++number;
        }
    }

    // Add button 0
    buttons[0] = new QPushButton("0", central);
    buttons[0]->setFixedSize(50, 50);
    gridLayout->addWidget(buttons[0], 3, 1);
    connect(buttons[0], &QPushButton::clicked, this, &MainWindow::digitClicked);


    //
    QGridLayout* gridLayoutOperator = new QGridLayout();
    vLayout->addLayout(gridLayoutOperator);

    int sizeButtonOperator = 40;
    addButton = new QPushButton("+", central);
    addButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(addButton, 0, 1);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    subButton = new QPushButton("-", central);
    subButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(subButton, 0, 2);
    connect(subButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    mulButton = new QPushButton("*", central);
    mulButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(mulButton, 0, 3);
    connect(mulButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    divButton = new QPushButton("/", central);
    divButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(divButton, 0, 4);
    connect(divButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    equalButton = new QPushButton("=", central);
    equalButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(equalButton, 1, 1);
    connect(equalButton, &QPushButton::clicked, this, &MainWindow::equalClicked);
    clearButton = new QPushButton("C", central);
    clearButton->setFixedSize(sizeButtonOperator, sizeButtonOperator);
    gridLayoutOperator->addWidget(clearButton, 1, 3);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearClicked);

}

void MainWindow::digitClicked()
{
    /* dynamic_cast, բայց սպեցիֆիկ է Qt-ին.
     * Your slot digitClicked() is connected to multiple buttons (0–9).
     * sender() tells you which one triggered the slot.
     * Using qobject_cast, you safely convert it to the correct type and get its text (the digit).
     */
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    QString clickedDigit = clickedButton->text();  // e.g., "1", "2", "3"
    QString currentDisplay = display->text();

    if (currentDisplay == "0" || waitingForSecondNumber) {
        display->setText(clickedDigit);
        waitingForSecondNumber = false;  // reset flag
    }
    else
        display->setText(currentDisplay + clickedDigit);
}

void MainWindow::operatorClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    pendingOperator = clickedButton->text();  // store operator: e.g., "+", "-", "/", "*"
    firstNumber = display->text().toDouble();  // save first number
    waitingForSecondNumber = true;  // next digit will start new number
}

void MainWindow::equalClicked() {
    double secondNumber = display->text().toDouble();
    double result = 0;

    if (pendingOperator == "+") result = firstNumber + secondNumber;
    else if (pendingOperator == "-") result = firstNumber - secondNumber;
    else if (pendingOperator == "*") result = firstNumber * secondNumber;
    else if (pendingOperator == "/") {
        if (secondNumber != 0)
            result = firstNumber / secondNumber;
        else {
            display->setText("Error");
            return;
        }
    }

    display->setText(QString::number(result));
    waitingForSecondNumber = true;   // ready for next operation
}

void MainWindow::clearClicked() {
    display->setText("0");
    firstNumber = 0;
    pendingOperator = "";
    waitingForSecondNumber = false;
}


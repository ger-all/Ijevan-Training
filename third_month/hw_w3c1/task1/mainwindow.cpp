#include "mainwindow.h"
// #include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 200);

    button = new QPushButton("Click me!", this);
    button->setGeometry(5, 50, 100, 30);

    label = new QLabel("...", this);
    label->setGeometry(50, 100, 150, 30);

    connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked() {
    label->setText("Hello, Qt!");
}


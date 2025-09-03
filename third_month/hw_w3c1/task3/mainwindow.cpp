#include "mainwindow.h"
#include <QVBoxLayout>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);

    button = new QPushButton("Press me", central);
    label = new QLabel("Pressed 0 times", central);

    layout->addWidget(button);
    layout->addWidget(label);

    // object1::signal -> app::slot
    connect(button, &QPushButton::clicked, this, &MainWindow::buttonClicked);
}

// app::slot -> emit app::signal -> object2::slot
void MainWindow::buttonClicked()
{
    // QApplication acts as mediator
    clickCount++;

    // Here "app emits a signal" — simulate by calling updateLabel slot
    updateLabel(clickCount);
}

// object2::slot
void MainWindow::updateLabel(int count)
{
    label->setText(QString("Pressed %1 times").arg(count));
}


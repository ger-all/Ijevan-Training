#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // explicit
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();  // slot to handle button click

private:
    QPushButton *button;
    QLabel *label;
};

#endif // MAINWINDOW_H


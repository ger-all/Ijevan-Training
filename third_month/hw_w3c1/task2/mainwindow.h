#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void digitClicked();  // slot for digit buttons
    void operatorClicked();
    void equalClicked();
    void clearClicked();

private:
    QLineEdit* display;
    QPushButton* buttons[10];  // buttons 0–9

    QPushButton *addButton;
    QPushButton *subButton;
    QPushButton *mulButton;
    QPushButton *divButton;

    QPushButton *equalButton;
    QPushButton *clearButton;

    // For calculator logic
    double firstNumber = 0;
    QString pendingOperator;
    bool waitingForSecondNumber = false;
};

#endif // MAINWINDOW_H


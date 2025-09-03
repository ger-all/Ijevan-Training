#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void buttonClicked();        // Slot in QApplication (mediator)
    void updateLabel(int count); // Slot in QLabel (via MainWindow)

private:
    QPushButton *button;
    QLabel *label;
    int clickCount = 0;
};

#endif // MAINWINDOW_H


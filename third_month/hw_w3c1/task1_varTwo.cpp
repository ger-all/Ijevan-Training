#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create a simple window
    QWidget window;
    window.setWindowTitle("My first  Qt app");
    window.resize(300, 200);

    // Create a label
    QLabel label("...", &window); // parent of label => window, window is deleted => label is also
    label.setGeometry(50, 100, 150, 30);

    // Create a button
    QPushButton button("Click me!", &window);
    button.setGeometry(50, 50, 100, 30);

    // Connect button click to label text change
    // if 3rd parameter is destroyed, signal also disconnected
    QObject::connect(&button, &QPushButton::clicked, &window, [&label]() {
        label.setText("Hello, Qt!");
    });

    window.show();
    return app.exec();
}


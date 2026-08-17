#include <QApplication>
#include "calculator_window.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    CalculatorWindow window;
    window.setWindowTitle("Calculator");
    window.resize(320, 420);
    window.show();
    return app.exec();
}

#ifndef CALCULATOR_WINDOW_H
#define CALCULATOR_WINDOW_H

#include <QMainWindow>
#include <QString>

class QLineEdit;
class QPushButton;
class QWidget;

class CalculatorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CalculatorWindow(QWidget* parent = nullptr);

private:
    void setupUI();

    // Calculation state
    double currentOperand_ = 0.0;
    double previousOperand_ = 0.0;
    QString pendingOperation_;
    bool isNewNumber_ = true;
    bool hasError_ = false;

    // UI widgets
    QLineEdit* display_;

    void appendDigit(const QString& digit);
    void handleDecimal();
    void handleOperation(const QString& op);
    void handleEquals();
    void handleClear();
    double compute(double left, const QString& op, double right);
    void formatDisplay(double value);
};

#endif // CALCULATOR_WINDOW_H

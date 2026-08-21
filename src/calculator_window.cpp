#include "calculator_window.h"
#include "math_utils.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QtGlobal>

CalculatorWindow::CalculatorWindow(QWidget* parent)
    : QMainWindow(parent) {
    setupUI();
}

void CalculatorWindow::setupUI() {
    auto* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto* layout = new QGridLayout(centralWidget);
    layout->setSpacing(5);
    layout->setContentsMargins(10, 10, 10, 10);

    // Display
    display_ = new QLineEdit(this);
    display_->setReadOnly(true);
    display_->setAlignment(Qt::AlignRight);
    display_->setFont(QFont(QStringLiteral("Sans"), 24));
    display_->setText("0");
    layout->addWidget(display_, 0, 0, 1, 4);

    // Button layout:
    //   Row 1: C      ⌫     .     /
    //   Row 2: 7      8     9     *
    //   Row 3: 4      5     6     -
    //   Row 4: 1      2     3     +
    //   Row 5: 0 (span 2 cols)  = (span 2 cols)
    const char* labels[5][4] = {
        {"C", "⌫", ".", "/"},
        {"7", "8", "9", "*"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "+"},
        {"0", "=", "", ""}  // last two empty — = will span cols 2-3
    };

    const char* digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            const char* label = labels[row][col];
            if (!label || !label[0])
                continue;  // skip filler slots in the last row

            int gridCol = col;
            int colspan = 1;

            // Last row: "0" spans cols 0-1, "=" spans cols 2-3
            if (row == 4 && col == 0)
                colspan = 2;
            else if (row == 4 && col == 1) {
                gridCol = 2;
                colspan = 2;
            }

            QPushButton* btn = new QPushButton(label, this);
            QFont font(QStringLiteral("Sans"), 18);
            btn->setFont(font);
            btn->setMinimumHeight(55);

            layout->addWidget(btn, row + 1, gridCol, 1, colspan);
            const QString& text = label;

            // Determine if it's a digit, decimal, clear, backspace, or operation
            bool isDigit = false;
            for (const char* d : digits) {
                if (text == d) { isDigit = true; break; }
            }

            if (isDigit) {
                QObject::connect(btn, &QPushButton::clicked, this, [this, text]() {
                    appendDigit(text);
                });
            } else if (text == ".") {
                QObject::connect(btn, &QPushButton::clicked, this, &CalculatorWindow::handleDecimal);
            } else if (text == "C") {
                QObject::connect(btn, &QPushButton::clicked, this, &CalculatorWindow::handleClear);
            } else if (text == "⌫") {
                QObject::connect(btn, &QPushButton::clicked, this, &CalculatorWindow::handleBackspace);
            } else if (text == "=") {
                QObject::connect(btn, &QPushButton::clicked, this, &CalculatorWindow::handleEquals);
            } else {
                // Operation: + - * /
                QObject::connect(btn, &QPushButton::clicked, this, [this, text]() {
                    handleOperation(text);
                });
            }
        }
    }

    display_->setStyleSheet("background-color: #f5f5f5; border-radius: 5px; padding: 10px;");
}

void CalculatorWindow::appendDigit(const QString& digit) {
    if (hasError_) {
        handleClear();
    }

    if (isNewNumber_) {
        display_->clear();
        isNewNumber_ = false;
    }

    // Prevent leading zeros like "007"
    if (display_->text() == "0") {
        display_->clear();
    }

    display_->insert(digit);
}

void CalculatorWindow::handleDecimal() {
    if (hasError_) {
        handleClear();
    }

    if (isNewNumber_) {
        display_->clear();
        display_->setText("0");
        isNewNumber_ = false;
    }

    if (!display_->text().contains('.')) {
        display_->insert(".");
    }
}

void CalculatorWindow::handleOperation(const QString& op) {
    if (hasError_) return;

    double current = display_->text().toDouble();

    try {
        if (!pendingOperation_.isEmpty() && !isNewNumber_) {
            // Chain operations: evaluate pending first
            previousOperand_ = compute(previousOperand_, pendingOperation_, current);
            formatDisplay(previousOperand_);
        } else {
            previousOperand_ = current;
        }
    } catch (const std::invalid_argument&) {
        // e.g. chained divide-by-zero: "5 / 0 *" must not terminate the app
        display_->setText("Error");
        hasError_ = true;
        pendingOperation_.clear();
        isNewNumber_ = true;
        return;
    }

    pendingOperation_ = op;
    isNewNumber_ = true;
}

void CalculatorWindow::handleEquals() {
    if (hasError_ || pendingOperation_.isEmpty()) return;

    double current = display_->text().toDouble();

    try {
        double result = compute(previousOperand_, pendingOperation_, current);
        formatDisplay(result);
        previousOperand_ = result;
        pendingOperation_.clear();
        isNewNumber_ = true;
    } catch (const std::invalid_argument&) {
        display_->setText("Error");
        hasError_ = true;
        pendingOperation_.clear();
        isNewNumber_ = true;
    }
}

void CalculatorWindow::handleClear() {
    previousOperand_ = 0.0;
    pendingOperation_.clear();
    isNewNumber_ = true;
    hasError_ = false;
    display_->setText("0");
}

void CalculatorWindow::handleBackspace() {
    if (hasError_) {
        handleClear();
        return;
    }

    QString text = display_->text();
    if (text.length() > 1) {
        text.chop(1);
        display_->setText(text);
    } else {
        display_->setText("0");
    }
}

double CalculatorWindow::compute(double left, const QString& op, double right) {
    if (op == "+") return calc::add(left, right);
    if (op == "-") return calc::subtract(left, right);
    if (op == "*") return calc::multiply(left, right);
    if (op == "/") return calc::divide(left, right);
    qWarning() << "compute(): unknown operator" << op;
    return right;
}

void CalculatorWindow::formatDisplay(double value) {
    // Use 'g' format for up to 15 significant digits, no trailing zeros
    QString text = QString::number(value, 'g', 15);
    display_->setText(text);
}

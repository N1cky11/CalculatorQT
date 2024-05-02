#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <vector>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <cmath>
#include <evaluate.h>

class CalculatorClass : public QWidget
{
    QLineEdit *display ;
    QString currentNumber{} ;
    QString expression{} ;
    Evaluate result ;
    Q_OBJECT
public:
    explicit CalculatorClass(QWidget *parent = nullptr);
    void plus() ;
    void minus() ;
    void multiply() ;
    void divide() ;
    void addDigit(int digit) ;
    void erase() ;
    void equal() ;
    int evaluate(std::string &tokens) ;
private slots:
  void digitPressed() ;
  void operandPressed() ;
};

bool isOperand(QString str) ;
bool isLastOperand(QLineEdit *display) ;
int precedence(char op) ;
int applyOperation(int a, int b, char op) ;


#include "calculatorclass.h"

using std::string ;
CalculatorClass::CalculatorClass(QWidget *parent)
    : QWidget{parent} , display(new QLineEdit("") )
{
    display->setGeometry(10,10,200,30) ;
    display->setReadOnly("true") ;

    auto plsBtn=new QPushButton("+",this) ;
    auto mnsBtn=new QPushButton("-",this) ;
    auto multBtn=new QPushButton("*",this) ;
    auto divBtn=new QPushButton("/",this) ;
    auto eraseBtn=new QPushButton("DEL",this) ;
    auto equalBtn=new QPushButton("=",this) ;
  //  auto deleteChar=new QPushButton("<-",this) ;

    auto *mainGrid=new QGridLayout(this) ;
    mainGrid->setSpacing(5) ;
    mainGrid->addWidget(display) ;
    std::vector<QPushButton*> buttons ;

    for(int i{} ; i<=9 ; ++i) {
      int row=3-(i-1)/3 ;
      int col=(i-1)%3 ;

      if(i==0) {
          row=4 ;
          col=0 ;
      }

      buttons.push_back(new QPushButton(QString::number(i),this)) ;
     // btn->setFixedSize(40,40) ;

      mainGrid->addWidget(buttons[i],row,col) ;

    connect(buttons[i],&QPushButton::clicked,this,&CalculatorClass::digitPressed ) ;
 }

    mainGrid->addWidget(plsBtn,4,1) ;
    mainGrid->addWidget(mnsBtn,1,4) ;
    mainGrid->addWidget(multBtn,2,4) ;
    mainGrid->addWidget(divBtn,3,4) ;
    mainGrid->addWidget(eraseBtn,4,4);
    mainGrid->addWidget(equalBtn,4,2) ;

    connect(mnsBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
    connect(plsBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
    connect(multBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
    connect(divBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
    connect(eraseBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
    connect(equalBtn,&QPushButton::clicked,this,&CalculatorClass::operandPressed) ;
}

void CalculatorClass::digitPressed() {
   QPushButton *button=qobject_cast<QPushButton*> (sender() ) ;
   if(!button) return ;
   auto buttonText=button->text() ;
   currentNumber+=buttonText[0] ;
   auto current=display->text() ;
   current+=buttonText[0] ;
   display->setText(current) ;
}

void CalculatorClass::plus() {
    bool removed=isLastOperand(display) ;
    if(removed) expression.chop(1) ;

    expression+='+' ;
    auto current=display->text() ;
    current+='+' ;
    display->setText(current) ;
}

void CalculatorClass::minus() {
    bool removed=isLastOperand(display) ;
     if(removed) expression.chop(1) ;

     expression+='-' ;
    auto current=display->text() ;
    current+='-' ;
    display->setText(current) ;
}

void CalculatorClass::multiply() {
    bool removed=isLastOperand(display) ;
    if(removed) expression.chop(1) ;

    expression+='*' ;
    auto current=display->text() ;
    current+='*' ;
    display->setText(current) ;
}

void CalculatorClass::divide() {
    bool removed=isLastOperand(display) ;
    if(removed) expression.chop(1) ;

    expression+='/' ;
    auto current=display->text() ;
    current+='/' ;
    display->setText(current) ;
}

void CalculatorClass::equal() {
    auto res=result(expression.toStdString() ) ;
    display-> setText(QString::number(res)) ;
    expression=QString::number(res) ;
    currentNumber.clear() ;
}

void CalculatorClass::erase() {
  display->setText("") ;
  expression.clear();
  currentNumber.clear() ;
}

bool isOperand(QString str) {
  if(str == "+" || str == "-" || str == "*" || str == "/") return true ;
  return false ;
}


bool isLastOperand(QLineEdit *display) {
    auto str=display->text() ;
    QChar last=str.right(1).at(0) ;
    if(isOperand(QString(last) ) ) {
      str.chop(1) ;
      display->setText(str) ;
      return true ;
    }
    return false ;
}

void CalculatorClass::operandPressed() {
    QPushButton *button=qobject_cast<QPushButton*> (sender() ) ;
    if(!button) return ;

    auto buttonText=button->text() ;
    expression+=currentNumber ;
    currentNumber="" ;

    if(buttonText=="+") plus() ;
     else if(buttonText=="-") minus() ;
      else if(buttonText=="*") multiply() ;
        else if(buttonText=="/") divide() ;
          else if(buttonText=="DEL") erase() ;
            else if(buttonText=="=") equal() ;
}

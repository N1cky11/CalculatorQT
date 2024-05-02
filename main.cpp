#include <QApplication>
#include "calculatorclass.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorClass obj ;
    obj.show() ;

    return a.exec();
}

#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);//qt���ø����̼� �����
    QtWidgetsApplication1 w;//��ü�� ����


    w.show();//â�� ����
    return a.exec();
}

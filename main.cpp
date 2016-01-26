#include "diagramtext.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiagramText w;
    w.show();
    return a.exec();
}

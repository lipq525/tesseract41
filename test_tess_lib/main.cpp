#include "test_tess_lib.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_tess_lib w;
    w.show();
    return a.exec();
}

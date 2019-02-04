#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication    app(argc, argv);
    QViewer         viewer(argc, argv);

    return viewer.exec();
}

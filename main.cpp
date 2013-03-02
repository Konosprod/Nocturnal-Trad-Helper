#include "mainwindow.h"
#include <QtGui>

using namespace std;

int main(int argc, char *argv[])
{
        QApplication app(argc,argv);
        MainWindow fenetre;

        QLibrary lib(QCoreApplication::applicationDirPath() + "/plugins/libtga.so.1.0.0");
        lib.load();
        if(!lib.isLoaded())
        {
            QMessageBox::warning(&fenetre, "Error", "Impossible de trouver le fichier:\n- plugins/libtga.so.1.0.0");
            return -1;
        }

        fenetre.setWindowTitle("Nocturnal Trad Helper v0.1");
        fenetre.show();
        return app.exec();
}

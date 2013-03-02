#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a_vbox = new QVBoxLayout;
    a_image = new QLabel;
    a_model = new QStringListModel;
    a_vbox->addWidget(a_image, 0, Qt::AlignCenter);
    ui->dispImage->setLayout(a_vbox);

    connect(ui->actionA_propos_de_QT, SIGNAL(triggered()), this, SLOT(aboutQT()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrirFichier()));
    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->listeMots, SIGNAL(clicked(QModelIndex)), this, SLOT(drawImage(QModelIndex)));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(sauverFicher()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    QMessageBox::about(this, "A propos de", "Cette application a pour but de traduire le jeu Nocturnal.\n"
                       "Pour savoir comment traduire et appliquer un patch veuillez vous reporter ici:\n- "
                       "http://konosprod.free.fr/blog/\n\n\nFait par Tartine");

}

void MainWindow::aboutQT()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::drawImage(QModelIndex index)
{
    QString filename = a_images.value(index.row());
    /*QMessageBox::information(this, "blah", QCoreApplication::applicationDirPath() + "/" + filename.toUpper());*/
    a_image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/" + filename.toUpper()));
}

void MainWindow::sauverFicher()
{
    if(ui->centralwidget->isEnabled())
    {
        QString name = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "(*.XML)");

        if(!name.isEmpty())
        {
            QFile flux(name);

            QStringList newNames = a_model->stringList();

            if(!flux.open(QFile::WriteOnly))
            {
                QMessageBox::critical(this, "Erreur", "Impossible de creer le fichier:\n- " + name);
                exit(-1);
            }
            else
            {
                QTextStream out(&flux);
                out << a_header;

                for(int i = 0; i < a_mots.count(); i++)
                {
                    out << "<Object FileName = \"" << a_images.value(i) << "\" bgpart = \"" << a_bgpart.value(i) << "\" id = \"" << a_id.value(i) << "\" name = \"" << newNames.value(i) << "\" x = \"" << a_x.value(i) << "\" y = \"" << a_y.value(i) << "\"/>\n";
                }
                out << "</Objects>";
                flux.close();
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Veuillez ouvrir un fichier avant.");
        return;
    }
}

void MainWindow::ouvrirFichier()
{
    a_y.clear();
    a_x.clear();
    a_id.clear();
    a_bgpart.clear();
    a_header.clear();
    a_mots.clear();
    a_images.clear();
    QString name = QFileDialog::getOpenFileName(this, "Selectionner un fichier", QString(), "(*.XML)");
    QFile file(name);
    QString chaine;

    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            chaine += line + '\n';
        }
        file.close();
        int fin;
        int i = chaine.indexOf("<?xml");
        if(i != -1)
        {
            fin = chaine.indexOf("<Objects>");
            if(fin != -1)
            {
                a_header += chaine.mid(i, fin+9);
            }
        }

        i = chaine.indexOf("name = \"");
        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+8);
            if(fin != -1)
            {
                a_mots << chaine.mid(i+8, fin-i-8);
            }
            else
            {
                fin = i + fin + 8;
            }

            i = chaine.indexOf("name = \"", fin);
        }
        i = chaine.indexOf("FileName = \"");

        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+12);
            if(fin != -1)
            {
                a_images << chaine.mid(i+12, fin-i-12);
            }
            else
            {
                fin = i + fin + 12;
            }

            i = chaine.indexOf("FileName = \"", fin);
        }

        i = chaine.indexOf("bgpart = \"");

        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+10);
            if(fin != -1)
            {
                a_bgpart << chaine.mid(i+10, fin-i-10);
            }
            else
            {
                fin += i + 12;
            }

            i = chaine.indexOf("bgpart = \"", fin);
        }

        i = chaine.indexOf("id = \"");

        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+6);
            if(fin != -1)
            {
                a_id << chaine.mid(i+6, fin-i-6);
            }
            else
            {
                fin += i +6;
            }

            i = chaine.indexOf("id = \"", fin);
        }

        i = chaine.indexOf("x = \"");

        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+5);
            if(fin != -1)
            {
                a_x << chaine.mid(i+5, fin-i-5);
            }
            else
            {
                fin += i + 6;
            }

            i = chaine.indexOf("x = \"", fin);
        }

        i = chaine.indexOf("y = \"");

        while(i != -1)
        {
            fin = chaine.indexOf("\"", i+5);
            if(fin != -1)
            {
                a_y << chaine.mid(i+5, fin-i-5);
            }
            else
            {
                fin += i + 6;
            }

            i = chaine.indexOf("y = \"", fin);
        }
    }

    a_model->setStringList(a_mots);
    ui->centralwidget->setEnabled(true);
    ui->listeMots->setModel(a_model);
}

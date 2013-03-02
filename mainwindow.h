#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
void ouvrirFichier();
void drawImage(QModelIndex index);
void sauverFicher();
void aboutQT();
void about();

private:
    Ui::MainWindow *ui;
    QLabel* a_image;
    QVBoxLayout* a_vbox;
    QString a_header;
    QStringList a_x;
    QStringList a_y;
    QStringList a_id;
    QStringList a_bgpart;
    QStringList a_mots;
    QStringList a_images;
    QStringListModel* a_model;
};

#endif // MAINWINDOW_H

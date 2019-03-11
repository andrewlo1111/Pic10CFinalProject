#include "mainwindow.h"
#include <QApplication>

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0,0,300,300);

    w.show();

    return a.exec();
}

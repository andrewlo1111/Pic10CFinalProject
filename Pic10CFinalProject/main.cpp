#include "mainwindow.h"
#include <QApplication>

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QStackedWidget *control_window = new QStackedWidget;
    QWidget *player_one_info = new QWidget;
    QWidget *player_two_info = new QWidget;

    QVBoxLayout *player_one_lay = new QVBoxLayout;
    QLabel *p1_label = new QLabel("Player 1 turn");
    QLabel *p1_money_label = new QLabel("Money: 100");
    QLabel *p1_food_label = new QLabel("Food: 100");
    QLabel *p1_mine_label = new QLabel("Mine Count: 0");
    QLabel *p1_farm_label = new QLabel("Farm Count: 0");
    QPushButton *p1_end_turn_button = new QPushButton("End Turn");

    QVBoxLayout *player_two_lay = new QVBoxLayout;
    QLabel *p2_label = new QLabel("Player 2 turn");
    QLabel *p2_money_label = new QLabel("Money: 100");
    QLabel *p2_food_label = new QLabel("Food: 100");
    QLabel *p2_mine_label = new QLabel("Mine Count: 0");
    QLabel *p2_farm_label = new QLabel("Farm Count: 0");
    QPushButton *p2_end_turn_button = new QPushButton("End Turn");


    player_one_lay->addWidget(p1_label);
    player_one_lay->addWidget(p1_money_label);
    player_one_lay->addWidget(p1_food_label);
    player_one_lay->addWidget(p1_mine_label);
    player_one_lay->addWidget(p1_farm_label);
    player_one_lay->addWidget(p1_end_turn_button);

    player_one_info->setLayout(player_one_lay);


    player_two_lay->addWidget(p2_label);
    player_two_lay->addWidget(p2_money_label);
    player_two_lay->addWidget(p2_food_label);
    player_two_lay->addWidget(p2_mine_label);
    player_two_lay->addWidget(p2_farm_label);
    player_two_lay->addWidget(p2_end_turn_button);

    player_one_info->setLayout(player_two_lay);

    QObject::connect(p1_end_turn_button,SIGNAL(clicked()),control_window,SLOT(setCurrentIndex(int)));

    control_window->setWindowTitle("Player 1 Information");
    control_window->addWidget(player_one_info);
    control_window->addWidget(player_two_info);
    control_window->setGeometry(200,200,200,200);
    control_window->show();
    w.show();

    return a.exec();
}

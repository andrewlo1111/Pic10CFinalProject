#include "mainwindow.h"
#include "ui_mainwindow.h"


void Unit::move()
{
    if(done == true)
    {
        return;
    }
    //some action is conducted
    done = true;
}

void Unit::defend()
{
    if(done == true)
    {
        return;
    }
    defense *= 1.25;
    done = true;
}

void Unit::attack_enemy(Unit other_unit)
{
    if(done == true)
    {
        return;
    }
    if(attack > other_unit.defense)
    {
        //wins battle
        done = true;
        return;
    }
    else
    {
        //lose battle and kills/deletes unit
    }
}

Villager::Villager()
{
    unit_type = "Villager";
    attack = 0.5;
    defense = 0.5;
}

void Villager::build()
{
    //ask for input for possible building
    std::string possible_buildings[3] = {"TownCenter", "Farm", "Mine"};
    //for loop to determine if possible then build
}

Warrior::Warrior()
{
    unit_type = "Warrior";
    attack = 1;
    defense = 1;
}

Archer::Archer()
{
    unit_type = "Archer";
    attack = .75;
    defense = 1.75;
}

Knight::Knight()
{
    unit_type = "Knight";
    attack = 2;
    defense = .75;
}



Mine::Mine()
{
    building_type = "Mine";
    durability = 2;
}

Farm::Farm()
{
    building_type = "Farm";
    durability = 2;
}

TownCenter::TownCenter()
{
    building_type = "TownCenter";
    durability = 3;
}



Player::Player():money(100), food(100), mine_count(0), farm_count(0), unit_list(0)
{
    QLabel *money_label = new QLabel("Money: 100");
    QLabel *food_label = new QLabel("Food: 100");
    QLabel *mine_label = new QLabel("Mines: 0");
    QLabel *farm_label = new QLabel("Farms: 0");

    label_arr.push_back(money_label);
    label_arr.push_back(food_label);
    label_arr.push_back(mine_label);
    label_arr.push_back(farm_label);
}

void Player::buildMine()
{
    mine_count += 1;
    QString text("Mines: " + QString::number(mine_count));
    label_arr[2]->setText(text);
}

void Player::buildFarm()
{
    farm_count += 1;
    QString text("Farms: " + QString::number(farm_count));
    label_arr[3]->setText(text);
}

int Player::get_money()
{
    return money;
}

int Player::get_food()
{
    return food;
}

int Player::get_mine_count()
{
    return mine_count;
}

int Player::get_farm_count()
{
    return farm_count;
}

std::vector<QLabel*> Player::get_label_arr()
{
    return label_arr;
}

void Player::add_money(int amount)
{
    money += amount;
}

void Player::add_food(int amount)
{
    food += amount;
}

void Player::train_unit(possible_unit new_unit)
{
    switch(new_unit)
    {
    case(villager):
    {
        Villager v1;
        unit_list.push_back(v1);
        break;
    }
    case(warrior):
    {
        Warrior w1;
        unit_list.push_back(w1);
        break;
    }
    case(archer):
    {
        Archer a1;
        unit_list.push_back(a1);
        break;
    }
    case(knight):
    {
        Knight k1;
        unit_list.push_back(k1);
        break;
    }
    }

}

void Player::updateMoney(QLabel* label)
{
    QString text("Money: " + QString::number(money));
    label->setText(text);
}

void Player::updateFood(QLabel* label)
{
    QString text("Food: " + QString::number(food));
    label->setText(text);
}

void Player::updateMine(QLabel* label)
{
    QString text("Mine Count: "+ QString::number(mine_count));
    label->setText(text);
}

void Player::updateFarm(QLabel* label)
{
    QString text("Farm Count: " + QString::number(farm_count));
    label->setText(text);
}


void MainWindow::end_turn_rewards(int player)
{
    if (player == 0)
    {
        p1.add_money(p1.get_mine_count() * 100);
        p1.add_food(p1.get_farm_count() * 100);
    }
    if (player == 1)
    {
        p2.add_money(p2.get_mine_count() * 100);
        p2.add_food(p2.get_farm_count() * 100);
    }
}

void MainWindow::update_labels(int player)
{
    if(player == 0)
    {
        QString money_text("Money: " + QString::number(p1.get_money()));
        QString food_text("Food: " + QString::number(p1.get_food()));
        QString mine_text("Mines: " + QString::number(p1.get_mine_count()));
        QString farm_text("Farms: " + QString::number(p1.get_farm_count()));

        QString text_arr[4] = {money_text, food_text, mine_text, farm_text};

        std::vector<QLabel*> label_vector = p1.get_label_arr();

        for(int i=0;i<4;i++)
        {
            label_vector[i]->setText(text_arr[i]);
        }
    }

    if(player == 1)
    {
        QString money_text("Money: " + QString::number(p2.get_money()));
        QString food_text("Food: " + QString::number(p2.get_food()));
        QString mine_text("Mines: " + QString::number(p2.get_mine_count()));
        QString farm_text("Farms: " + QString::number(p2.get_farm_count()));

        QString text_arr[4] = {money_text, food_text, mine_text, farm_text};

        std::vector<QLabel*> label_vector = p2.get_label_arr();

        for(int i=0;i<4;i++)
        {
            label_vector[i]->setText(text_arr[i]);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStackedWidget *control_window = new QStackedWidget;

    p1.buildMine();
    p1.buildFarm();
    p2.buildFarm();

    QWidget *player_one_info = new QWidget;
    QWidget *player_two_info = new QWidget;
    QButtonGroup *end_turn_buttons = new QButtonGroup;

    //player one layout with labels and buttons
    QVBoxLayout *player_one_lay = new QVBoxLayout;
    QHBoxLayout *p1_food_money_lay = new QHBoxLayout;
    QHBoxLayout *p1_farm_mine_lay = new QHBoxLayout;
    QLabel *p1_label = new QLabel("Player 1 turn");
    QPushButton *p1_end_turn_button = new QPushButton("End Turn");


    //player two layout with labels and buttons
    QVBoxLayout *player_two_lay = new QVBoxLayout;
    QHBoxLayout *p2_food_money_lay = new QHBoxLayout;
    QHBoxLayout *p2_farm_mine_lay = new QHBoxLayout;
    QLabel *p2_label = new QLabel("Player 2 turn");
    QPushButton *p2_end_turn_button = new QPushButton("End Turn");

    //added two buttons to the button group to change stacked widget index later
    end_turn_buttons->addButton(p1_end_turn_button,1);
    end_turn_buttons->addButton(p2_end_turn_button,0);

    //player one adding additional labels
    player_one_lay->addWidget(p1_label);
    for(unsigned int i= 0;i<4;i++)
    {
        if(i < 2)
        {
            p1_food_money_lay->addWidget(p1.get_label_arr()[i]);
        }
        else
        {
            p1_farm_mine_lay->addWidget(p1.get_label_arr()[i]);
        }
    }
    player_one_lay->addLayout(p1_food_money_lay);
    player_one_lay->addLayout(p1_farm_mine_lay);
    player_one_lay->addWidget(p1_end_turn_button);

    player_one_info->setLayout(player_one_lay);

    //player two adding additional labels
    player_two_lay->addWidget(p2_label);
    for(unsigned int i=0;i<4;i++)
    {
        if(i<2)
        {
            p2_food_money_lay->addWidget(p2.get_label_arr()[i]);
        }
        else
        {
            p2_farm_mine_lay->addWidget(p2.get_label_arr()[i]);
        }

    }

    player_two_lay->addLayout(p2_food_money_lay);
    player_two_lay->addLayout(p2_farm_mine_lay);
    player_two_lay->addWidget(p2_end_turn_button);

    player_two_info->setLayout(player_two_lay);


    control_window->setWindowTitle("Player Info");
    control_window->addWidget(player_one_info);
    control_window->addWidget(player_two_info);


    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),control_window,SLOT(setCurrentIndex(int)));
    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),this, SLOT(end_turn_rewards(int)));
    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)), this, SLOT(update_labels(int)));
    control_window->setGeometry(200,200,200,200);
    control_window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}




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


void Villager::build(int row, int col)
{
    //build the building at specific row and col
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
    durability = 1;
}

Farm::Farm()
{
    building_type = "Farm";
    durability = 1;
}

TownCenter::TownCenter()
{
    building_type = "TownCenter";
    durability = 2;
}



Player::Player():money(100), food(100), mine_count(0), farm_count(0), town_center_count(0), unit_list(0)
{
    QLabel *money_label = new QLabel("Money: 100");
    QLabel *food_label = new QLabel("Food: 100");
    QLabel *mine_label = new QLabel("Mines: 0");
    QLabel *farm_label = new QLabel("Farms: 0");
    QLabel *unit_label = new QLabel("Unit Count: 0");

    label_arr.push_back(money_label);
    label_arr.push_back(food_label);
    label_arr.push_back(mine_label);
    label_arr.push_back(farm_label);
    label_arr.push_back(unit_label);

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

unsigned int Player::get_unit_count()
{
    return unit_list.size();
}

std::vector<QLabel*> Player::get_label_arr()
{
    return label_arr;
}

bool Player::lose()
{
    if(get_unit_count() == 0 && town_center_count == 0 )
    {
        return true;
    }
    return false;
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
    if(enough_resources(new_unit)== false)
    {
        return;
    }
    switch(new_unit)
    {
    case(villager):
    {
        Villager v1;
        unit_list.push_back(v1);
        this->money -= 50;
        this->food -= 50;
        break;

    }
    case(warrior):
    {
        Warrior w1;
        unit_list.push_back(w1);
        this->money -= 100;
        this->food -= 100;
        break;
    }
    case(archer):
    {
        Archer a1;
        unit_list.push_back(a1);
        this->money -= 100;
        this->food -= 100;
        break;
    }
    case(knight):
    {
        Knight k1;
        unit_list.push_back(k1);
        this->money -= 150;
        this->food -= 150;
        break;
    }
    }

}

bool Player::enough_resources(possible_unit unit)
{
    switch(unit)
    {
    case(villager):
    {
        if(money <50 || food <50)
        {
            return false;
        }
        break;
    }
    case(warrior):
    {
        if(money < 100 || food <100)
        {
            return false;
        }
        break;
    }
    case(archer):
    {
        if(money<100 || food < 100)
        {
            return false;
        }
        break;
    }
    case(knight):
    {
        if(money<150 || food<150)
        {
            return false;
        }
        break;
    }
    }
    return true;
}



void MainWindow::end_turn_rewards(int player)
{
    if (player == 0)
    {
        p1.add_money(p1.get_mine_count() * 100);
        p1.add_food(p1.get_farm_count() * 100);
        p1_turn = false;
        change_select(1,0);
    }
    if (player == 1)
    {
        p2.add_money(p2.get_mine_count() * 100);
        p2.add_food(p2.get_farm_count() * 100);
        p1_turn = true;
        change_select(5,4);
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

        for(unsigned int i=0;i<4;i++)
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

        for(unsigned int i=0;i<4;i++)
        {
            label_vector[i]->setText(text_arr[i]);
        }
    }
}

void MainWindow::p1_update_units()
{
    QString unit_text("Unit Count: " + QString::number(p1.get_unit_count()));
    p1.get_label_arr()[4]->setText(unit_text);
}

void MainWindow::p2_update_units()
{
    QString unit_text("Unit Count: " + QString::number(p2.get_unit_count()));
    p2.get_label_arr()[4]->setText(unit_text);
}

void MainWindow::change_select(int row, int col)
{
    selected_spot[0] = row;
    selected_spot[1] = col;
    processandRepaint();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    this->drawMap(&painter);
    this->highlight_selected(&painter);
    this->drawUnits(&painter);

}


void MainWindow::processandRepaint()
{
    QCoreApplication::processEvents();
    this->repaint();
}

void MainWindow::drawMap(QPainter *painter)
{
    QPen pen(Qt::black, 2, Qt::SolidLine);
    painter->setPen(pen);
    for(int i= 0; i<7;i++)
    {
        painter->drawLine(0, i*50, 300, i*50);                   //change spots by 50
        painter->drawLine(i*50, 0, i*50, 300);
    }


}

void MainWindow::drawUnits(QPainter *painter)
{
    for(int row =0; row<6; row++)
    {
        for(int col = 0; col <6; col++)
        {
            QRect rectangle(col * 50, row * 50, 50, 50 );
            QFont font = painter->font();
            font.setPointSize(25);
            painter->setFont(font);
            if(player_indicator[row][col] == player_one)
            {
                painter->setBrush(Qt::red);
                painter->setPen(Qt::red);
            }
            if(player_indicator[row][col] == player_two)
            {
                painter->setBrush(Qt::blue);
                painter->setPen(Qt::blue);
            }
            switch(game_board[row][col])
            {
            case(empty):
            {
                break;
            }
            case(town_center):
            {
                //draw some house
                painter->drawEllipse(rectangle);
                //painter->fillRect(rectangle, Qt::red);
                break;
            }
            case(mine):
            {
                //draw some mine
                QString text("M");
                //set color to red
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            case(farm):
            {
                //draw farm
                QString text("F");
                //set color to red
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            case(villager):
            {
                //draw villager
                QString text("V");
                //set color to red
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            case(warrior):
            {
                //draw warrior
                QString text("W");
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            case(archer):
            {
                //draw archer
                QString text("A");
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            case(knight):
            {
                //draw knight
                QString text("K");
                painter->drawText(rectangle, Qt::AlignCenter, text);
                break;
            }
            }
        }
    }
}


void MainWindow::highlight_selected(QPainter *painter)
{
    int row = selected_spot[0];
    int col = selected_spot[1];
    QRect rectangle(col*50, row*50, 50, 50);
    painter->drawRect(rectangle);
    painter->fillRect(rectangle, Qt::green);
}

void MainWindow::choosingUnit(QString selected_unit)
{
    if(selected_unit == "Villager")
    {
        potential_unit = Player::villager;
    }
    else if (selected_unit == "Warrior")
    {
        potential_unit = Player::warrior;
    }
    else if (selected_unit == "Archer")
    {
        potential_unit = Player::archer;
    }
    else if (selected_unit == "Knight")
    {
        potential_unit = Player::knight;
    }
}

MainWindow::occupied MainWindow::convert_to_occupied(Player::possible_unit potential_unit)
{
    if( potential_unit == Player::villager)
    {
        return MainWindow::villager;
    }
    else if(potential_unit == Player::warrior)
    {
        return MainWindow::warrior;
    }
    else if(potential_unit == Player::archer)
    {
        return MainWindow::archer;
    }
    else if(potential_unit == Player::knight)
    {
        return MainWindow::knight;
    }
    else
    {
        return MainWindow::town_center;   // used as a debugging mechanism
    }
}



void MainWindow::p1_train_unit()
{

    if(p1.enough_resources(potential_unit) == false)
    {
        return;
    }
    auto train = [this](int row, int col) {
        p1.train_unit(potential_unit);
        MainWindow::occupied new_unit = convert_to_occupied(potential_unit);
        game_board[row][col] = new_unit;
        player_indicator[row][col] = player_one;
        processandRepaint();
    };
    if(game_board[1][0] == empty)
    {
        train(1,0);
    }
    else if(game_board[0][1] == empty)
    {
        train(0,1);
    }
}

void MainWindow::p2_train_unit()
{
    if(p2.enough_resources(potential_unit) == false)
    {
        return;
    }
    auto train = [this](int row, int col){
        p2.train_unit(potential_unit);
        MainWindow::occupied new_unit = convert_to_occupied(potential_unit);
        game_board[row][col] = new_unit;
        player_indicator[row][col] = player_two;
        processandRepaint();
    };
    if(game_board[5][4] == empty)
    {
        train(5,4);
    }
    else if(game_board[4][5] == empty)
    {
        train(4,5);
    }
    else
    {
        return;
    }
}

void MainWindow::move()
{
    int row = selected_spot[0];
    int col = selected_spot[1];
    game_board[row + 1][col] = game_board[row][col];
    game_board[row][col] = empty;
    player_indicator[row+1][col] = player_indicator[row][col];
    player_indicator[row][col] = none;
    processandRepaint();
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p1_turn = true;
    selected_spot[0] = 1;
    selected_spot[1] = 0;
    for(int row = 0;row<6;row++)     //setup for board at very start of the game
    {
        for(int col = 0; col<6; col++)
        {
            if(row == 0 && col==0 )
            {
                game_board[row][col] = town_center;
                player_indicator[row][col] = player_one;
            }
            else if(row == 5 && col ==5)
            {
                game_board[row][col] = town_center;
                player_indicator[row][col] = player_two;
            }
            else
            {
                game_board[row][col] = empty;
                player_indicator[row][col] = none;
            }
        }
    }

    QStackedWidget *control_window = new QStackedWidget;

    QWidget *player_one_info = new QWidget;
    QWidget *player_two_info = new QWidget;
    QButtonGroup *end_turn_buttons = new QButtonGroup;
    QButtonGroup *train_unit_buttons = new QButtonGroup;

    //player one layout with labels and buttons
    QVBoxLayout *player_one_lay = new QVBoxLayout;
    QHBoxLayout *p1_food_money_lay = new QHBoxLayout;
    QHBoxLayout *p1_farm_mine_lay = new QHBoxLayout;

    QLabel *p1_label = new QLabel("Player 1 turn");
    p1_label->setAlignment(Qt::AlignCenter);
    QFont font = p1_label->font();
    font.setBold(true);
    font.setPointSize(10);
    p1_label->setFont(font);

    QPushButton *p1_end_turn_button = new QPushButton("End Turn");
    QPushButton *p1_train_unit_button = new QPushButton("Train Unit");
    //combobox to select unit you want to train
    QLabel *select_unit_label = new QLabel("Select Unit: ");

    QString units[4] = {"Villager", "Warrior", "Archer", "Knight"};
    QComboBox *select_unit = new QComboBox;
    auto select = [units](QComboBox* box) {
        for(int i=0;i<4;i++)
        {
            box->addItem(units[i]);
        }
    };
    select(select_unit);

    //player two layout with labels and buttons
    QVBoxLayout *player_two_lay = new QVBoxLayout;
    QHBoxLayout *p2_food_money_lay = new QHBoxLayout;
    QHBoxLayout *p2_farm_mine_lay = new QHBoxLayout;

    QLabel *p2_label = new QLabel("Player 2 turn");
    p2_label->setAlignment(Qt::AlignCenter);
    p2_label->setFont(font);

    QPushButton *p2_end_turn_button = new QPushButton("End Turn");
    //combo box to select unit you want to train
    QLabel *select_unit_label2 = new QLabel("Select Unit: ");
    QComboBox *select_unit2 = new QComboBox;
    select(select_unit2);
    QPushButton *p2_train_unit_button = new QPushButton("Train Unit");   //confirms whatever is selected on combo box



    //added two buttons to the button group to change stacked widget index later
    end_turn_buttons->addButton(p1_end_turn_button,1);
    end_turn_buttons->addButton(p2_end_turn_button,0);

    train_unit_buttons->addButton(p1_train_unit_button, 0);
    train_unit_buttons->addButton(p2_train_unit_button, 1);

    //player one adding additional labels
    player_one_lay->addWidget(p1_label);
    for(unsigned int i= 0;i<5;i++)
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
    player_one_lay->addWidget(select_unit_label);
    player_one_lay->addWidget(select_unit);
    player_one_lay->addWidget(p1_train_unit_button);
    player_one_lay->addWidget(p1_end_turn_button);


    player_one_info->setLayout(player_one_lay);

    //player two adding additional labels
    player_two_lay->addWidget(p2_label);
    for(unsigned int i=0;i<5;i++)
    {
        if(i < 2)
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
    player_two_lay->addWidget(select_unit_label2);
    player_two_lay->addWidget(select_unit2);
    player_two_lay->addWidget(p2_train_unit_button);
    player_two_lay->addWidget(p2_end_turn_button);


    player_two_info->setLayout(player_two_lay);

    control_window->setWindowTitle("Player Info");
    control_window->addWidget(player_one_info);
    control_window->addWidget(player_two_info);

    QPushButton *button = new QPushButton("move");

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(move()));
    button->show();

    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),control_window,SLOT(setCurrentIndex(int)));
    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),this, SLOT(end_turn_rewards(int)));
    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)), this, SLOT(update_labels(int)));

    QObject::connect(select_unit, SIGNAL(currentIndexChanged(QString)), this, SLOT(choosingUnit(QString)));
    QObject::connect(p1_train_unit_button, SIGNAL(clicked()), this, SLOT(p1_train_unit()));
    QObject::connect(p1_train_unit_button, SIGNAL(clicked()), this, SLOT(p1_update_units()));

    QObject::connect(select_unit2, SIGNAL(currentIndexChanged(QString)), this, SLOT(choosingUnit(QString)));
    QObject::connect(p2_train_unit_button, SIGNAL(clicked()), this, SLOT(p2_train_unit()));
    QObject::connect(p2_train_unit_button, SIGNAL(clicked()), this, SLOT(p2_update_units()));

    QObject::connect(train_unit_buttons, SIGNAL(buttonClicked(int)), this, SLOT(update_labels(int)));

    control_window->setGeometry(300,200,300,200);
    control_window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}




#include "mainwindow.h"
#include "ui_mainwindow.h"






bool Unit::win_battle(Unit other_unit)
{
    if(attack > other_unit.defense)
    {
        //wins battle
        return true;
    }
    else
    {
        //lose battle and kills/deletes unit
        return false;
    }
}


Villager::Villager()
{
    unit_type = "Villager";
    attack = 0.5;
    defense = 0.5;
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
    defense = 1.5;
}

Knight::Knight()
{
    unit_type = "Knight";
    attack = 2;
    defense = .75;
}

Player::Player():money(100), food(100), mine_count(0), farm_count(0), town_center_count(1), unit_count(0), move_count(3)
{
    QLabel *money_label = new QLabel("Money: 100");
    QLabel *food_label = new QLabel("Food: 100");
    QLabel *mine_label = new QLabel("Mines: 0");
    QLabel *farm_label = new QLabel("Farms: 0");
    QLabel *move_label = new QLabel("Moves: 3");

    label_arr.push_back(money_label);
    label_arr.push_back(food_label);
    label_arr.push_back(mine_label);
    label_arr.push_back(farm_label);
    label_arr.push_back(move_label);

}

void Player::buildMine()
{
    mine_count += 1;
    add_money(-100);
    add_food(-100);
    QString text("Mines: " + QString::number(mine_count));
    label_arr[2]->setText(text);
}

void Player::buildFarm()
{
    farm_count += 1;
    add_money(-100);
    add_food(-100);
    QString text("Farms: " + QString::number(farm_count));
    label_arr[3]->setText(text);
}

void Player::buildTC()
{
    town_center_count += 1;
    add_money(-100);
    add_food(-100);
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

int Player::get_town_center_count()
{
    return town_center_count;
}

int Player::get_unit_count()
{
    return unit_count;
}

std::vector<QLabel*> Player::get_label_arr()
{
    return label_arr;
}

int Player::get_move_count()
{
    return move_count;
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

void Player::town_center_destroyed()
{
    town_center_count--;
}

void Player::mine_destroyed()
{
    mine_count--;
}

void Player::farm_destroyed()
{
    farm_count--;
}

void Player::unit_died()
{
    unit_count--;
}

void Player::train_unit(possible_unit new_unit)
{
    if(enough_resources(new_unit)== false)
    {
        return;
    }
    unit_count++;
    switch(new_unit)
    {
    case(villager):
    {
        this->money -= 50;
        this->food -= 50;
        break;

    }
    case(warrior):
    {
        this->money -= 100;
        this->food -= 100;
        break;
    }
    case(archer):
    {
        this->money -= 100;
        this->food -= 100;
        break;
    }
    case(knight):
    {
        this->money -= 150;
        this->food -= 150;
        break;
    }
    }

}

void Player::used_move()
{
    move_count--;
}

void Player::reset_move()
{
    move_count = 3;
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
    if (player == 0)                                    //when player 2 ends turn
    {
        p1.add_money(p1.get_mine_count() * 100 + p1.get_town_center_count() *50);
        p1.add_food(p1.get_farm_count() * 100 + p1.get_town_center_count() * 50);
        potential_unit = Player::villager;              //resets default to villager
        change_select(1,0);
        p1.reset_move();
        p1_turn = true;
        update_labels(player);
    }
    if (player == 1)                                   //when player1 ends turn
    {
        p2.add_money(p2.get_mine_count() * 100 + p2.get_town_center_count() * 50);
        p2.add_food(p2.get_farm_count() * 100 + p2.get_town_center_count() * 50);
        potential_unit = Player::villager;              //resets default to villager
        change_select(5,4);
        p2.reset_move();
        p1_turn = false;
        update_labels(player);
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
        QString moves_text("Moves: " + QString::number(p1.get_move_count()));


        QString text_arr[5] = {money_text, food_text, mine_text, farm_text, moves_text};

        std::vector<QLabel*> label_vector = p1.get_label_arr();

        for(unsigned int i=0;i<5;i++)
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
        QString moves_text("Moves: " + QString::number(p2.get_move_count()));

        QString text_arr[5] = {money_text, food_text, mine_text, farm_text, moves_text};

        std::vector<QLabel*> label_vector = p2.get_label_arr();

        for(unsigned int i=0;i<5;i++)
        {
            label_vector[i]->setText(text_arr[i]);
        }
    }
}

void MainWindow::update_move()
{
    if(p1_turn == true)
    {
        QString moves_text("Moves: " + QString::number(p1.get_move_count()));
        p1.get_label_arr()[4]->setText(moves_text);
    }
    else
    {
        QString moves_text("Moves: " + QString::number(p2.get_move_count()));
        p2.get_label_arr()[4]->setText(moves_text);
    }
}


void MainWindow::change_select(int row, int col)
{
    selected_spot[0] = row;
    selected_spot[1] = col;


    processandRepaint();
    if(game_board[row][col] == villager)
    {
        QVBoxLayout *build_lay = new QVBoxLayout;
        QPushButton *move = new QPushButton("Move");
        QPushButton *build_mine = new QPushButton("Build Mine");
        QPushButton *build_farm = new QPushButton("Build Farm");
        QPushButton *build_tc = new QPushButton("Build TownCenter");

        QPushButton* build_button_arr[4] = {move, build_mine, build_farm, build_tc};
        for(int i=0;i<4;i++)
        {
            build_lay->addWidget(build_button_arr[i]);
        }
        QObject::connect(build_button_arr[0], SIGNAL(clicked()), this, SLOT(hide_build_window()));
        QObject::connect(build_button_arr[1], SIGNAL(clicked()), this, SLOT(build_mine()));
        QObject::connect(build_button_arr[2], SIGNAL(clicked()), this, SLOT(build_farm()));
        QObject::connect(build_button_arr[3], SIGNAL(clicked()), this, SLOT(build_TC()));

        this->build_window->setLayout(build_lay);
        this->build_window->show();
    }

    else {
        this->build_window->hide();
    }

}

void MainWindow::hide_build_window()
{
    this->build_window->hide();
}

void MainWindow::select_to_cursor()
{
    int row = cursor[0];
    int col = cursor[1];
    //can only change select onto a spot that is not owned by enemy
    if((p1_turn == true && player_indicator[row][col] == player_one) || (p1_turn == false && player_indicator[row][col] == player_two))
    {
        change_select(row, col);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    this->drawMap(&painter);
    this->highlight_cursor(&painter);
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

void MainWindow::highlight_cursor(QPainter *painter)
{
    int row = cursor[0];
    int col = cursor[1];
    QRect rectangle(col* 50, row* 50, 50, 50);
    painter->drawRect(rectangle);
    painter->fillRect(rectangle, Qt::yellow);
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

void MainWindow::build_mine()
{
    int cursor_row = cursor[0];
    int cursor_col = cursor[1];
    int selected_row = selected_spot[0];
    int selected_col = selected_spot[1];
    int distance = abs(selected_row - cursor_row) + abs(selected_col - cursor_col);
    if(game_board[cursor_row][cursor_col] == empty && distance == 1 )      //build spot must be empty and adjacent to villager
    {
        if(p1_turn == true )
        {
            p1.buildMine();
            game_board[cursor_row][cursor_col] = mine;              //build at location of cursor
            player_indicator[cursor_row][cursor_col] = player_one;
            processandRepaint();
        }
        else
        {
            p2.buildMine();
            game_board[cursor_row][cursor_col] = mine;
            player_indicator[cursor_row][cursor_col] = player_two;
            processandRepaint();
        }
   }
}

void MainWindow::build_farm()
{
    int cursor_row = cursor[0];
    int cursor_col = cursor[1];
    int selected_row = selected_spot[0];
    int selected_col = selected_spot[1];
    int distance = abs(selected_row - cursor_row) + abs(selected_col - cursor_col);
    if(game_board[cursor_row][cursor_col] == empty && distance == 1 )      //build spot must be empty and adjacent to villager
    {
        if(p1_turn == true )
        {
            p1.buildFarm();
            game_board[cursor_row][cursor_col] = farm;              //build at location of cursor
            player_indicator[cursor_row][cursor_col] = player_one;
            processandRepaint();
        }
        else
        {
            p2.buildFarm();
            game_board[cursor_row][cursor_col] = farm;
            player_indicator[cursor_row][cursor_col] = player_two;
            processandRepaint();
        }
   }
}

void MainWindow::build_TC()
{
    int cursor_row = cursor[0];
    int cursor_col = cursor[1];
    int selected_row = selected_spot[0];
    int selected_col = selected_spot[1];
    int distance = abs(selected_row - cursor_row) + abs(selected_col - cursor_col);
    if(game_board[cursor_row][cursor_col] == empty && distance == 1 )      //build spot must be empty and adjacent to villager
    {
        if(p1_turn == true )
        {
            p1.buildTC();
            game_board[cursor_row][cursor_col] = town_center;              //build at location of cursor
            player_indicator[cursor_row][cursor_col] = player_one;
            processandRepaint();
        }
        else
        {
            p2.buildTC();
            game_board[cursor_row][cursor_col] = town_center;
            player_indicator[cursor_row][cursor_col] = player_two;
            processandRepaint();
        }
   }
}

void MainWindow::moveCursorUp()
{
    if(cursor[0] > 0)
    {
        cursor[0] -= 1;
        processandRepaint();
    }
    return;
}

void MainWindow::moveCursorDown()
{
    if(cursor[0] < 5 )
    {
        cursor[0] += 1;
        processandRepaint();
    }
    return;
}

void MainWindow::moveCursorLeft()
{
    if(cursor[1] > 0)
    {
        cursor[1] -= 1;
        processandRepaint();
    }
    return;
}

void MainWindow::moveCursorRight()
{
    if(cursor[1] < 5)
    {
        cursor[1] += 1;
        processandRepaint();
    }
    return;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int cursor_row = cursor[0];
    int cursor_col = cursor[1];
    int select_row = selected_spot[0];
    int select_col = selected_spot[1];
    bool same_spot = false;
    if(cursor_row == select_row && cursor_col == select_col)
    {
        same_spot = true;
    }

    auto is_movable_unit = [this,cursor_row,cursor_col](){
        if(game_board[cursor_row][cursor_col] == warrior)
        {
            return true;
        }
        else if(game_board[cursor_row][cursor_col] == archer)
        {
            return true;
        }
        else if (game_board[cursor_row][cursor_col] == knight)
        {
            return true;
        }
        else if (game_board[cursor_row][cursor_col]== villager && build_window->isHidden())
        {
            return true;
        }
        return false;
    };
    if(same_spot == true && is_movable_unit())
    {
        switch(event->key())
        {
            case Qt::Key_Left:
                this->moveLeft();
                break;
            case Qt::Key_Right:
                this->moveRight();
                break;
            case Qt::Key_Up:
                this->moveUp();
                break;
            case Qt::Key_Down:
                this->moveDown();
        }
    }
    else
    {
        switch(event->key())
        {
            case Qt::Key_Left:
                this->moveCursorLeft();
                break;
            case Qt::Key_Right:
                this->moveCursorRight();
                break;
            case Qt::Key_Up:
                this->moveCursorUp();
                break;
            case Qt::Key_Down:
                this->moveCursorDown();
                break;
            case Qt::Key_Enter:
            case Qt::Key_Return:
                this->select_to_cursor();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
}

bool MainWindow::is_ally(int other_row, int other_col)
{
    int current_row = selected_spot[0];
    int current_col = selected_spot[1];
    if(player_indicator[current_row][current_col] == player_indicator[other_row][other_col])
    {
        return true;
    }
    return false;
}

bool MainWindow::is_enemy(int other_row, int other_col)
{
    int current_row = selected_spot[0];
    int current_col = selected_spot[1];
    MainWindow::owner current_owner = player_indicator[current_row][current_col];
    MainWindow::owner other_owner = player_indicator[other_row][other_col];
    if(current_owner== player_one && other_owner == player_two)
    {
        return true;
    }
    else if(current_owner == player_two && other_owner == player_one)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MainWindow::is_empty(int other_row, int other_col)
{
    if(player_indicator[other_row][other_col] == none)
    {
        return true;
    }
    return false;
}

bool MainWindow::selecting_empty()
{
    int row = selected_spot[0];
    int col = selected_spot[1];
    if(game_board[row][col] == empty && player_indicator[row][col] == none)
    {
        return true;
    }
    return false;
}

void MainWindow::move_complete()
{
    if(p1_turn == true)
    {
        p1.used_move();
    }
    else
    {
        p2.used_move();
    }
    update_move();
}

void MainWindow::attack(int other_row, int other_col)
{
    MainWindow::occupied enemy = game_board[other_row][other_col];
    if(enemy == town_center || enemy == mine || enemy == farm)
    {
        attack_building(other_row, other_col);
    }
    else
    {
        attack_unit(other_row, other_col);
    }
    processandRepaint();
}

void MainWindow::attack_building(int other_row, int other_col)
{
    int current_row = selected_spot[0];
    int current_col = selected_spot[1];
    MainWindow::occupied current_unit = game_board[current_row][current_col];
    if(current_unit == villager)                //villagers cannot destroy buildings
    {
        return;
    }
    else
    {
        MainWindow::occupied destroyed = game_board[other_row][other_col];
        if(destroyed == town_center)
        {
            if(p1_turn == true)
            {
                p2.town_center_destroyed();
            }
            else
            {
                p1.town_center_destroyed();
            }
        }
        else if(destroyed == mine)
        {
            if(p1_turn == true)
            {
                p2.mine_destroyed();
            }
            else
            {
                p1.mine_destroyed();
            }
        }
        else if(destroyed == farm)
        {
            if(p1_turn == true)
            {
                p2.farm_destroyed();
            }
            else
            {
                p1.farm_destroyed();
            }
        }
        game_board[other_row][other_col] = empty;           //building instantly destroyed
        player_indicator[other_row][other_col] = none;
    }
}

void MainWindow::attack_unit(int other_row, int other_col)
{
    Villager v;
    Warrior w;
    Archer a;
    Knight k;
    int current_row = selected_spot[0];
    int current_col = selected_spot[1];
    MainWindow::occupied current_unit = game_board[current_row][current_col];
    MainWindow::occupied other_unit = game_board[other_row][other_col];
    Unit attacker;
    Unit defender;
    switch(current_unit)
    {
        case villager:
            attacker = v;
            break;
        case warrior:
            attacker = w;
            break;
        case archer:
            attacker = a;
            break;
        case knight:
            attacker = k;
            break;
        default:
            break;
    }
    switch(other_unit)
    {
        case villager:
            defender = v;
            break;
        case warrior:
            defender = w;
            break;
        case archer:
            defender = a;
            break;
        case knight:
            defender = k;
            break;
        default:
            break;
    }
    if(attacker.win_battle(defender) == true)               //if attacker wins then attacker moves to spot of defender and defender is gone
    {
        game_board[other_row][other_col] = current_unit;
        game_board[current_row][current_col] = empty;
        player_indicator[other_row][other_col] = player_indicator[current_row][current_col];
        player_indicator[current_row][current_col]= none;
        if(p1_turn == true)
        {
            p2.unit_died();
        }
        else
        {
            p1.unit_died();
        }
    }
    else                                                    //attacker losing means spot now is empty
    {
        game_board[current_row][current_col] = empty;
        player_indicator[current_row][current_col] = none;
        if(p1_turn == true)
        {
            p1.unit_died();
        }
        else
        {
            p2.unit_died();
        }
    }
}

void MainWindow::moveUp()
{
    if(p1_turn == true && p1.get_move_count() == 0)
    {
        return;
    }
    else if(p1_turn == false && p2.get_move_count() == 0)
    {
        return;
    }
    int row = selected_spot[0];
    int col = selected_spot[1];
    int desired_row = row-1;
    int desired_col = col;
    if(this->selecting_empty() || row == 0)    //cannot move if selecting empty spot or on top row
    {
        return;
    }
    if(is_ally(desired_row, desired_col) == true)
    {
        return;
    }
    else if(is_empty(desired_row, desired_col) == true )    //cannot move up if off board or to ally
    {
        game_board[desired_row][desired_col] = game_board[row][col];
        game_board[row][col] = empty;
        player_indicator[desired_row][desired_col]= player_indicator[row][col];
        player_indicator[row][col] = none;
        processandRepaint();
    }
    else if(is_enemy(desired_row,desired_col) == true)
    {
        attack(desired_row, desired_col);
    }
    move_complete();

    return;

}

void MainWindow::moveDown()
{
    if(p1_turn == true && p1.get_move_count() == 0)
    {
        return;
    }
    else if(p1_turn == false && p2.get_move_count() == 0)
    {
        return;
    }
    int row = selected_spot[0];
    int col = selected_spot[1];
    int desired_row = row+1;
    int desired_col = col;
    if(this->selecting_empty() || row == 5)    //cannot move if selecting empty spot or bottom
    {
        return;
    }
    if(is_ally(desired_row,desired_col) == true)             //cannot move if ally occupies
    {
        return;
    }
    else if(is_empty(desired_row, desired_col) == true)
    {
        game_board[desired_row][desired_col] = game_board[row][col];
        game_board[row][col] = empty;
        player_indicator[desired_row][desired_col] = player_indicator[row][col];
        player_indicator[row][col] = none;
        processandRepaint();
    }
    else if(is_enemy(desired_row,desired_col) == true)
    {
        attack(desired_row,desired_col);
    }
    move_complete();
    return;
}

void MainWindow::moveLeft()
{
    if(p1_turn == true && p1.get_move_count() == 0)
    {
        return;
    }
    else if(p1_turn == false && p2.get_move_count() == 0)
    {
        return;
    }
    int row = selected_spot[0];
    int col = selected_spot[1];
    int desired_row = row;
    int desired_col = col -1;
    if(this->selecting_empty() || col == 0)    //cannot move if selecting empty spot or left edge
    {
        return;
    }
    if(is_ally(desired_row, desired_col) == true)
    {
        return;
    }
    else if(is_empty(desired_row, desired_col) == true)
    {
        game_board[desired_row][desired_col] = game_board[row][col];
        game_board[row][col] = empty;
        player_indicator[desired_row][desired_col] = player_indicator[row][col];
        player_indicator[row][col] = none;
        processandRepaint();
    }
    else if(is_enemy(desired_row, desired_col)== true)
    {
        attack(desired_row, desired_col);
    }
    move_complete();
    return;
}

void MainWindow::moveRight()
{
    if(p1_turn == true && p1.get_move_count() == 0)
    {
        return;
    }
    else if(p1_turn == false && p2.get_move_count() == 0)
    {
        return;
    }
    int row = selected_spot[0];
    int col = selected_spot[1];
    int desired_row = row;
    int desired_col = col + 1;
    if(this->selecting_empty() || col ==5)    //cannot move if selecting empty spot or right edge
    {
        return;
    }
    if(is_ally(desired_row,desired_col) == true)
    {
        return;
    }
    else if(is_empty(desired_row, desired_col) == true)
    {
        game_board[desired_row][desired_col] = game_board[row][col];
        game_board[row][col] = empty;
        player_indicator[desired_row][desired_col] = player_indicator[row][col];
        player_indicator[row][col] = none;
        processandRepaint();
    }
    else if(is_enemy(desired_row, desired_col) == true)
    {
        attack(desired_row,desired_col);
    }
    move_complete();
    return;
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p1_turn = true;
    cursor[0] = 0;                  //sets base cursor at top left
    cursor[1] = 0;
    selected_spot[0] = 0;
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

    QPushButton *move_up_but = new QPushButton("Up");
    QPushButton *move_down_but = new QPushButton("Down");
    QPushButton *move_left_but = new QPushButton("Left");
    QPushButton *move_right_but = new QPushButton("Right");
    QPushButton *enter_button = new QPushButton("Enter");

    QPushButton* move_arr[5] = {move_up_but, move_down_but, move_left_but, move_right_but,  enter_button};
    QObject::connect(move_arr[0], SIGNAL(clicked()), this, SLOT(moveUp()));
    QObject::connect(move_arr[1], SIGNAL(clicked()), this, SLOT(moveDown()));
    QObject::connect(move_arr[2], SIGNAL(clicked()), this, SLOT(moveLeft()));
    QObject::connect(move_arr[3], SIGNAL(clicked()), this, SLOT(moveRight()));
    QObject::connect(move_arr[4], SIGNAL(clicked()), this, SLOT(select_to_cursor()));

    QWidget *move_window = new QWidget;
    QHBoxLayout *move_lay = new QHBoxLayout;
    for(int i=0;i<5;i++)
    {
        move_lay->addWidget(move_arr[i]);
    }
    move_window->setLayout(move_lay);
    move_window->show();


    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),control_window,SLOT(setCurrentIndex(int)));
    QObject::connect(end_turn_buttons,SIGNAL(buttonClicked(int)),this, SLOT(end_turn_rewards(int)));


    QObject::connect(select_unit, SIGNAL(currentIndexChanged(QString)), this, SLOT(choosingUnit(QString)));
    QObject::connect(p1_train_unit_button, SIGNAL(clicked()), this, SLOT(p1_train_unit()));

    QObject::connect(select_unit2, SIGNAL(currentIndexChanged(QString)), this, SLOT(choosingUnit(QString)));
    QObject::connect(p2_train_unit_button, SIGNAL(clicked()), this, SLOT(p2_train_unit()));

    QObject::connect(train_unit_buttons, SIGNAL(buttonClicked(int)), this, SLOT(update_labels(int)));

    control_window->setGeometry(300,200,300,200);
    control_window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}




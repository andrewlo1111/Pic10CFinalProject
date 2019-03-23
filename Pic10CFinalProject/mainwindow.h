#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <string>
#include <vector>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QPainter>
#include <QString>
#include <QKeyEvent>
#include <iostream>
#include <cmath>


class Unit
{
public:
    Unit():unit_type("Unit"),attack(1),defense(1){}

    bool win_battle(Unit other_unit);

protected:
    std::string unit_type;
    double attack;
    double defense;



};

class Villager: public Unit
{
public:
    Villager();

};

class Warrior:public Unit
{
public:
    Warrior();
};

class Archer:public Unit
{
public:
    Archer();
};

class Knight:public Unit
{
public:
    Knight();
};



class  Building
{
public:
    Building(): building_type("Building"), durability(1) {}
  protected:
    std::string building_type;
    int durability;

};

class Farm: public Building
{
public:
    Farm();
};

class Mine: public Building
{
public:
    Mine();
};

class TownCenter: public Building
{
public:
    TownCenter();
};




class Player
{
public:
    enum possible_unit {villager, warrior, archer, knight};

    Player();

    void buildMine();
    void buildFarm();
    void buildTC();

    int get_money();
    int get_food();
    int get_mine_count();
    int get_farm_count();
    int get_town_center_count();
    int get_move_count();
    unsigned int get_unit_count();
    std::vector<QLabel*> get_label_arr();

    bool enough_resources(possible_unit);
    bool lose();


    void add_money(int amount);
    void add_food(int amount);
    void train_unit(possible_unit new_unit);
    void used_move();
    void reset_move();


private:
    int money;
    int food;
    int mine_count;
    int farm_count;
    int town_center_count;
    std::vector<QLabel*> label_arr;
    std::vector<Unit> unit_list;
    int move_count;


};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum owner{none, player_one, player_two};
    enum occupied{empty, town_center, mine, farm, villager, warrior, archer, knight};

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);


public slots:
    void end_turn_rewards(int player);        //int passed determines which player gets the benefit
    void update_labels(int player);
    void update_move();
    void choosingUnit(QString selected_unit);
    void p1_train_unit();
    void p2_train_unit();
    void hide_build_window();

    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
    void select_to_cursor();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void build_mine();
    void build_farm();
    void build_TC();

private:
    Ui::MainWindow *ui;
    Player p1;
    Player p2;
    bool p1_turn;
    Player::possible_unit potential_unit = Player::villager;    //current selected unit on combo box
    MainWindow::occupied game_board[6][6];              //indicates unit on board
    MainWindow::owner player_indicator[6][6];           //indicates who owns the unit on board
    int selected_spot[2];                                   //first element will be row, second element will be column
    int cursor[2];                                          //first element is row, second element is column
    QWidget *build_window = new QWidget;


    //painting functions
    void paintEvent(QPaintEvent *e);
    void processandRepaint();
    void drawMap(QPainter *painter);
    void drawUnits(QPainter *painter);
    void highlight_selected(QPainter *painter);
    void highlight_cursor(QPainter *painter);
    void move_complete();



    //helper functions
    MainWindow::occupied convert_to_occupied(Player::possible_unit);
    void change_select(int row, int col);
    bool is_ally(int other_row, int other_col);
    bool is_enemy(int other_row, int other_col);
    bool is_empty(int other_row, int other_col);
    bool selecting_empty();
    void attack(int other_row, int other_col);
    void attack_unit(int other_row, int other_col);
    void attack_building(int other_row, int other_col);


};



#endif // MAINWINDOW_H

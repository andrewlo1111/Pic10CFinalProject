#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <string>
#include <vector>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>


class Unit
{
public:
    Unit():unit_type("Unit"),attack(1),defense(1),done(false){}
    void move();
    void defend();
    void attack_enemy(Unit other_unit);
protected:
    std::string unit_type;
    double attack;
    double defense;
    bool done = false;

};

class Villager: public Unit
{
public:
    Villager();
    void build();

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
    Building(): building_type("Building"), durability(2) {}
  protected:
    std::string building_type;
    int durability;

};

class Farm:Building
{
public:
    Farm();
};

class Mine:Building
{
public:
    Mine();
};

class TownCenter:Building
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

    int get_money();
    int get_food();
    int get_mine_count();
    int get_farm_count();
    std::vector<QLabel*> get_label_arr();


    void add_money(int amount);
    void add_food(int amount);
    void train_unit(possible_unit new_unit);

    void updateMoney(QLabel* label);
    void updateFood(QLabel* label);
    void updateMine(QLabel* label);
    void updateFarm(QLabel* label);



private:
    int money;
    int food;
    int mine_count;
    int farm_count;
    std::vector<QLabel*> label_arr;
    std::vector<Unit> unit_list;

};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void end_turn_rewards(int player);        //int passed determines which player gets the benefit
    void update_labels(int player);

private:
    Ui::MainWindow *ui;
    Player p1;
    Player p2;


};



#endif // MAINWINDOW_H

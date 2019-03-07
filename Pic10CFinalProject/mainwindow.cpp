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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

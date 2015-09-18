#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Treasure
{
public:
    double xCoord, yCoord;
    string loot;
};

class User
{
public:
    double xCoord, yCoord;
    string name;
    double moveDist;
};

class Enemy
{
public:
    double xCoord, yCoord;
    double aggroDist;
    bool aggro;
    string type;
};

double distToUser(double xUser, double yUser, double xObj, double yObj){
    double distance = sqrt(pow((xUser-xObj),2.0)+pow((yUser-yObj),2.0)); //Pythaogrean theorem (aka distance formula)
    return distance;

}


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Treasure chest;
    chest.xCoord = rand()%50-25;
    chest.yCoord = rand()%50-25;

    User user;
    user.xCoord = rand()%50-25;
    user.yCoord = rand()%50-25;
    user.moveDist = 1.0;

    Enemy monster;
    monster.aggro = true;
    monster.aggroDist = 5*1.414;

    while(monster.aggro == true)//makes sure that user isn't eaten when they spawn
    {
        monster.xCoord = rand()%50-25;
        monster.yCoord = rand()%50-25;
        if(distToUser(user.xCoord,user.yCoord,monster.xCoord,monster.yCoord) > monster.aggroDist)
            monster.aggro = false;
    }


    char dir = ' ';
    bool gameOver = false;
    while(gameOver == false){
        system("cls");

    cout << "User x: " << user.xCoord << "\tUser y: " << user.yCoord;
    cout << "\nChest x: " << chest.xCoord << "\tChest y: " << chest.yCoord;
    cout << "\nEnemy x: " << monster.xCoord << "\tEnemy y: " << monster.yCoord << endl;
    char worldMap[50][50];
    for(int i = 0; i<50; ++i){
        for(int j = 0; j<50; ++j){
            worldMap[i][j] = '.';
        }
    }
    worldMap[int(24 - user.yCoord)][int(user.xCoord+24)] = 'o';
    worldMap[24][24] = '+';
    worldMap[int(24-monster.yCoord)][int(monster.xCoord +24)] = '%';
    worldMap[int(24-chest.yCoord)][int(chest.xCoord + 24)] = '$';

    for(int i = 0; i<50; ++i){
        for(int j = 0; j<50; ++j){
            cout << worldMap[i][j];
        }
        cout << endl;
    }

        cout << "Distance to Treasure: " << distToUser(user.xCoord,user.yCoord,chest.xCoord,chest.yCoord) << ".\n";
        //whichever axis is closer generates the shiver
        if(abs(user.xCoord-monster.xCoord) < abs(user.yCoord-monster.yCoord)){
            if(user.xCoord-monster.xCoord > 0){
                cout << "There seems to be something dangerous to the west...\n";
            } else if(user.xCoord-monster.xCoord < 0){
                cout << "There seems to be something dangerous to the east...\n";
            }
        } else if(abs(user.xCoord-monster.xCoord) > abs(user.yCoord-monster.yCoord)){
            if(user.yCoord-monster.yCoord > 0){
                cout << "There seems to be something dangerous to the south...\n";
            } else if(user.yCoord-monster.yCoord < 0){
                cout << "There seems to be something dangerous to the north...\n";
            }
        }

        cout << "\nWhich direction (n,s,e,w) do you head?\n";
        cin >> dir;
        switch(dir){
        case 'n':
            user.yCoord += user.moveDist;
            break;
        case 's':
            user.yCoord -= user.moveDist;
            break;
        case 'e':
            user.xCoord += user.moveDist;
            break;
        case 'w':
            user.xCoord -= user.moveDist;
            break;
        default:
            cout << "What direction is that?\n";
            break;
        }

        //check for gameover
        if(distToUser(user.xCoord,user.yCoord,monster.xCoord,monster.yCoord) < monster.aggroDist){
            monster.aggro = true;
            gameOver = true;
            cout << "The monster noticed you and ate you alive.\n\nGAME OVER\n";
        }

        if(user.xCoord == chest.xCoord && user.yCoord == chest.yCoord){
            gameOver = true;
            cout << "You found the treasure. Nice!\n\n";
        }
    }

    int x = 0;
    cin >> x;
    return 0;
}

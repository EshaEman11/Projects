#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
using namespace std;
// Global Variable
char maze[24][71];
int pacmanX = 9;  // X Coordinate of Pacman
int pacmanY = 31; // Y Coordinate of Pacman
int score = 0;
int ghostX = 16;  // X Coordinate of Ghost
int ghost1X = 16; // X Coordinate of Ghost
int ghostY = 3;   // Y Coordinate of Ghost
int ghost1Y = 3;  // Y Coordinate of Ghost
int verX = 16;
int verY = 3;
int horX = 21;
int horY = 3;
int pX = 16;
int pY = 3;

char previousItem2 = ' ';
char previousItem = ' ';
char previousItem1 = ' ';
char previousItem3 = ' ';
char random_prev = ' ';
int moveCount = 0;
int it = 0;
int mit = 100;
bool energizer = false;

void printmaze();
void gotoxy(int x, int y);
void calculateScore();
void printScore();
void moveleft();
void moveright();
void moveup();
void movedown();
int ghostdirection();
bool ghostmovement();
int random_ghost();
bool moverandom_ghost();
void loadfromfile();
int ghostdirection1();
bool ghostmovement1();
bool vertical_ghost();
int ghost_vertical();
bool horizontal_ghost();
void gameover();
void energyleft();
void energyright();
void energyup();
void energydown();
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{

    loadfromfile();
    bool gamerunning = true;
    system("cls");
    SetConsoleTextAttribute(color, 13);
    printmaze();
    SetConsoleTextAttribute(color, 15);
    gotoxy(pacmanY, pacmanX);
    cout << "P";

    while (gamerunning)
    {

        Sleep(55);
        gotoxy(80, 10);
        printScore();

        if ((energizer == true && it <= mit))
        {
            while (it <= mit)
            {
                Sleep(55);
                if (energizer)
                {
                        SetConsoleTextAttribute(color, 6);
                    gotoxy(75, 11);

                    cout << "Iterations Left : " << mit - it << " ";
                        SetConsoleTextAttribute(color, 11);
                }
                it++;

                if (GetAsyncKeyState(VK_LEFT))
                {
                    energyleft();
                }
                if (GetAsyncKeyState(VK_RIGHT))
                {
                    energyright();
                }
                if (GetAsyncKeyState(VK_UP))
                {
                    energyup();
                }
                if (GetAsyncKeyState(VK_DOWN))
                {
                    energydown();
                }
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    gamerunning = false;
                }
            }
            energizer = false;
            it = 0;
        }
        else
        {
            energizer = false;
            it = 0;
        }
        SetConsoleTextAttribute(color, 9);
        if (ghostmovement() && ghostmovement1() && vertical_ghost() && horizontal_ghost())
        {

            gamerunning = true;
        }
        else
        {
            if (energizer)
            {
                gamerunning = true;
            }
            else
            {
                gamerunning = false;
            }
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveleft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveright();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveup();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movedown();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            gamerunning = false;
        }
    }
    gameover();
}

void printmaze()
{
    for (int row = 0; row < 24; row = row + 1)
    {
        for (int col = 0; col < 71; col = col + 1)
        {
            cout << maze[row][col];
        }
        cout << endl;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void calculateScore()
{
    score = score + 1;
}

void printScore()
{
    SetConsoleTextAttribute(color, 11);
    cout << "Score: " << score << endl;
    SetConsoleTextAttribute(color, 15);
}

void gameover()
{
    SetConsoleTextAttribute(color, 11);
    system("cls");
    printmaze();
    printScore();
    cout << "GAME OVER." << endl;
    Sleep(500);
    system("pause");
    system("cls");
    exit(0);
    SetConsoleTextAttribute(color, 15);
}

void moveleft()
{
    SetConsoleTextAttribute(color, 6);
    if (maze[pacmanX][pacmanY - 1] == 'o')
    {
        energizer = true;
    }
    if (maze[pacmanX][pacmanY - 1] == 'G' || maze[pacmanX][pacmanY - 1] == 'H' || maze[pacmanX][pacmanY - 1] == 'V' || maze[pacmanX][pacmanY - 1] == 'F')
    {

        gameover();
    }
    else if (maze[pacmanX][pacmanY - 1] != '#' && maze[pacmanX][pacmanY - 1] != '%' && maze[pacmanX][pacmanY - 1] != '|' || maze[pacmanX][pacmanY - 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
    SetConsoleTextAttribute(color, 15);
}

void moveright()
{
    SetConsoleTextAttribute(color, 6);
    if (maze[pacmanX][pacmanY + 1] == 'o')
    {
        energizer = true;
    }
    if (maze[pacmanX][pacmanY + 1] == 'G' || maze[pacmanX][pacmanY + 1] == 'H' || maze[pacmanX][pacmanY + 1] == 'V' || maze[pacmanX][pacmanY + 1] == 'F')
    {

        gameover();
    }
    else if (maze[pacmanX][pacmanY + 1] != '#' && maze[pacmanX][pacmanY + 1] != '%' && maze[pacmanX][pacmanY + 1] != '|' || maze[pacmanX][pacmanY + 1] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
    SetConsoleTextAttribute(color, 15);
}

void moveup()
{
    SetConsoleTextAttribute(color, 6);
    if (maze[pacmanX - 1][pacmanY] == 'o')
    {
        energizer = true;
    }
    if (maze[pacmanX - 1][pacmanY] == 'G' || maze[pacmanX - 1][pacmanY] == 'H' || maze[pacmanX - 1][pacmanY] == 'V' || maze[pacmanX - 1][pacmanY] == 'F')
    {

        gameover();
    }
    else if (maze[pacmanX - 1][pacmanY] != '#' && maze[pacmanX - 1][pacmanY] != '%' && maze[pacmanX - 1][pacmanY] != '|' || maze[pacmanX - 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {

            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
    SetConsoleTextAttribute(color, 15);
}

void movedown()
{
    SetConsoleTextAttribute(color, 6);
    if (maze[pacmanX + 1][pacmanY] == 'o')
    {
        energizer = true;
    }
    if (maze[pacmanX + 1][pacmanY] == 'G' || maze[pacmanX + 1][pacmanY] == 'H' || maze[pacmanX + 1][pacmanY] == 'V' || maze[pacmanX + 1][pacmanY] == 'F')
    {

        gameover();
    }
    else if (maze[pacmanX + 1][pacmanY] != '#' && maze[pacmanX + 1][pacmanY] != '%' && maze[pacmanX + 1][pacmanY] != '|' || maze[pacmanX + 1][pacmanY] == '.')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
    SetConsoleTextAttribute(color, 15);
}

int ghostdirection()
{
    if (moveCount == 5)
    {
        srand(time(0));
        int result = 1 + (rand() % 4);
        moveCount = 0;
        return result;
    }
    moveCount++;
    int horizontal = pacmanY - ghostY;
    int vertical = pacmanX - ghostX;
    int absX, absY;
    absX = vertical;
    if (vertical < 0)
    {
        absX = absX * (-1);
    }
    absY = horizontal;
    if (horizontal < 0)
    {
        absY = absY * (-1);
    }
    if (absX > absY)
    {
        if (vertical < 0)
            return 3;
        else
            return 4;
    }
    else
    {
        if (horizontal < 0)
            return 1;
        else
            return 2;
    }
}

bool ghostmovement()
{
    int value = ghostdirection();
    if (value == 1)
    {
        if (maze[ghostX][ghostY - 1] == ' ' || maze[ghostX][ghostY - 1] == '.' || maze[ghostX][ghostY - 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            if (maze[ghostX][ghostY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghostY = ghostY - 1;
            previousItem = maze[ghostX][ghostY];
            if (maze[ghostX][ghostY] == 'P')
            {

                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 2)
    {

        if (maze[ghostX][ghostY + 1] == ' ' || maze[ghostX][ghostY + 1] == '.' || maze[ghostX][ghostY + 1] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            cout << previousItem;
            ghostY = ghostY + 1;
            previousItem = maze[ghostX][ghostY];
            if (maze[ghostX][ghostY] == 'P')
            {

                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 3)
    {
        if (maze[ghostX - 1][ghostY] == ' ' || maze[ghostX - 1][ghostY] == '.' || maze[ghostX - 1][ghostY] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            if (maze[ghostX][ghostY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghostX = ghostX - 1;
            previousItem = maze[ghostX][ghostY];
            if (maze[ghostX][ghostY] == 'P')
            {

                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    if (value == 4)
    {
        if (maze[ghostX + 1][ghostY] == ' ' || maze[ghostX + 1][ghostY] == '.' || maze[ghostX + 1][ghostY] == 'P')
        {
            maze[ghostX][ghostY] = previousItem;
            gotoxy(ghostY, ghostX);
            if (maze[ghostX][ghostY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghostX = ghostX + 1;
            previousItem = maze[ghostX][ghostY];
            if (maze[ghostX][ghostY] == 'P')
            {

                return 0;
            }
            maze[ghostX][ghostY] = 'G';
            gotoxy(ghostY, ghostX);
            cout << "G";
        }
    }
    return 1;
}
int ghostdirection1()
{

    srand(time(0));
    int result = 1 + (rand() % 4);
    return result;
}

bool ghostmovement1()
{
    int value = ghostdirection1();
    if (value == 1)
    {
        if (maze[ghost1X][ghost1Y - 1] == ' ' || maze[ghost1X][ghost1Y - 1] == '.' || maze[ghost1X][ghost1Y - 1] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            gotoxy(ghost1Y, ghost1X);
            if (maze[ghost1X][ghost1Y] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghost1Y = ghost1Y - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (maze[ghost1X][ghost1Y] == 'P')
            {
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'F';
            gotoxy(ghost1Y, ghost1X);
            cout << "F";
        }
    }
    if (value == 2)
    {
        if (maze[ghost1X][ghost1Y + 1] == ' ' || maze[ghost1X][ghost1Y + 1] == '.' || maze[ghost1X][ghost1Y + 1] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            gotoxy(ghost1Y, ghost1X);
            cout << previousItem1;
            ghost1Y = ghost1Y + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (maze[ghost1X][ghost1Y] == 'P')
            {
                return 0;
            }
            maze[ghost1X][ghost1Y] = 'F';
            gotoxy(ghost1Y, ghost1X);
            cout << "F";
        }
    }
    if (value == 3)
    {
        if (maze[ghost1X - 1][ghost1Y] == ' ' || maze[ghost1X - 1][ghost1Y] == '.' || maze[ghost1X - 1][ghost1Y] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            gotoxy(ghost1Y, ghost1X);
            if (maze[ghost1X][ghost1Y] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghost1X = ghost1X - 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (maze[ghost1X][ghost1Y] == 'P')
            {

                return 0;
            }
            maze[ghost1X][ghost1Y] = 'F';
            gotoxy(ghost1Y, ghost1X);
            cout << "F";
        }
    }
    if (value == 4)
    {
        if (maze[ghost1X + 1][ghost1Y] == ' ' || maze[ghost1X + 1][ghost1Y] == '.' || maze[ghost1X + 1][ghost1Y] == 'P')
        {
            maze[ghost1X][ghost1Y] = previousItem1;
            gotoxy(ghost1Y, ghost1X);
            if (maze[ghost1X][ghost1Y] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            ghost1X = ghost1X + 1;
            previousItem1 = maze[ghost1X][ghost1Y];
            if (maze[ghost1X][ghost1Y] == 'P')
            {

                return 0;
            }
            maze[ghost1X][ghost1Y] = 'F';
            gotoxy(ghost1Y, ghost1X);
            cout << "F";
        }
    }
    return 1;
}

void loadfromfile()
{
    fstream file;
    string line;
    file.open("maze.txt", ios::in);
    for (int row = 0; row < 24; row++)
    {
        getline(file, line);
        for (int col = 0; col < 71; col++)
        {
            maze[row][col] = line[col];
        }
    }
    file.close();
}

int ghost_vertical()
{

    srand(time(0));
    int result = 3 + (rand() % 2);
    return result;
}

bool vertical_ghost()
{
    int value = ghost_vertical();
    if (value == 3)
    {

        if (maze[verX - 1][verY] == ' ' || maze[verX - 1][verY] == '.' || maze[verX - 1][verY] == 'P')
        {
            maze[verX][verY] = previousItem2;
            gotoxy(verY, verX);
            if (maze[verX][verY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            verX = verX - 1;
            previousItem2 = maze[verX][verY];
            if (maze[verX][verY] == 'P')
            {

                return 0;
            }
            maze[verX][verY] = 'V';
            gotoxy(verY, verX);
            cout << "V";
        }
    }
    if (value == 4)
    {
        if (maze[verX + 1][verY] == ' ' || maze[verX + 1][verY] == '.' || maze[verX + 1][verY] == 'P')
        {
            maze[verX][verY] = previousItem2;
            gotoxy(verY, verX);
            if (maze[verX][verY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            verX = verX + 1;
            previousItem2 = maze[verX][verY];
            if (maze[verX][verY] == 'P')
            {

                return 0;
            }
            maze[verX][verY] = 'V';
            gotoxy(verY, verX);
            cout << "V";
        }
    }
    return 1;
}

int ghost_horizontal()
{
    srand(time(0));
    int result = 1 + (rand() % 2);
    return result;
}

bool horizontal_ghost()
{
    int value = ghost_horizontal();
    if (value == 1)
    {
        if (maze[horX][horY - 1] == ' ' || maze[horX][horY - 1] == '.' || maze[horX][horY - 1] == 'P')
        {
            maze[horX][horY] = previousItem3;
            gotoxy(horY, horX);
            if (maze[horX][horY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            horY = horY - 1;
            previousItem3 = maze[horX][horY];
            if (previousItem3 == 'P')
            {
                return 0;
            }
            maze[horX][horY] = 'H';
            gotoxy(horY, horX);
            cout << "H";
        }
    }
    if (value == 2)
    {
        if (maze[horX][horY + 1] == ' ' || maze[horX][horY + 1] == '.' || maze[horX][horY + 1] == 'P')
        {
            maze[horX][horY] = previousItem3;
            gotoxy(horY, horX);
            if (maze[horX][horY] == '.')
            {
                cout << ".";
            }
            else
            {
                cout << " ";
            }
            horY = horY + 1;
            previousItem3 = maze[horX][horY];
            if (previousItem3 == 'P')
            {
                return 0;
            }
            maze[horX][horY] = 'H';
            gotoxy(horY, horX);
            cout << "H";
        }
    }
    return 1;
}

void energyleft()
{
    if (maze[pacmanX][pacmanY - 1] == 'o')
    {
        mit = 30;
    }

    else if (maze[pacmanX][pacmanY - 1] != '#' && maze[pacmanX][pacmanY - 1] != '%' && maze[pacmanX][pacmanY - 1] != '|' || maze[pacmanX][pacmanY - 1] == '.' || maze[pacmanX][pacmanY - 1] == 'V' || maze[pacmanX][pacmanY - 1] == 'F' || maze[pacmanX][pacmanY - 1] == 'H' || maze[pacmanX][pacmanY - 1] == 'G')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

void energyright()
{
    if (maze[pacmanX][pacmanY + 1] == 'o')
    {
        mit = 30;
    }

    else if (maze[pacmanX][pacmanY + 1] != '#' && maze[pacmanX][pacmanY + 1] != '%' && maze[pacmanX][pacmanY + 1] != '|' || maze[pacmanX][pacmanY + 1] == '.' || maze[pacmanX][pacmanY + 1] == 'V' || maze[pacmanX][pacmanY + 1] == 'F' || maze[pacmanX][pacmanY + 1] == 'H' || maze[pacmanX][pacmanY + 1] == 'G')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanY = pacmanY + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

void energyup()
{
    if (maze[pacmanX - 1][pacmanY] == 'o')
    {
        mit = 30;
    }

    else if (maze[pacmanX - 1][pacmanY] != '#' && maze[pacmanX - 1][pacmanY] != '%' && maze[pacmanX - 1][pacmanY] != '|' || maze[pacmanX - 1][pacmanY] == '.' || maze[pacmanX - 1][pacmanY] == 'V' || maze[pacmanX - 1][pacmanY] == 'F' || maze[pacmanX - 1][pacmanY] == 'H' || maze[pacmanX - 1][pacmanY] == 'G')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX - 1;
        if (maze[pacmanX][pacmanY] == '.')
        {

            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

void energydown()
{
    if (maze[pacmanX + 1][pacmanY] == 'o')
    {
        mit = 30;
    }

    else if (maze[pacmanX + 1][pacmanY] != '#' && maze[pacmanX + 1][pacmanY] != '%' && maze[pacmanX + 1][pacmanY] != '|' || maze[pacmanX + 1][pacmanY] == '.' || maze[pacmanX + 1][pacmanY] == 'V' || maze[pacmanX + 1][pacmanY] == 'F' || maze[pacmanX + 1][pacmanY] == 'H' || maze[pacmanX + 1][pacmanY] == 'G')
    {
        maze[pacmanX][pacmanY] = ' ';
        gotoxy(pacmanY, pacmanX);
        cout << " ";
        pacmanX = pacmanX + 1;
        if (maze[pacmanX][pacmanY] == '.')
        {
            calculateScore();
        }
        maze[pacmanX][pacmanY] = 'P';
        gotoxy(pacmanY, pacmanX);
        cout << "P";
    }
}

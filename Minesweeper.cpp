
#include <conio.h>
#include <iostream>
#include <ctime> 
using namespace std;

#define		N_MINE		10			
#define		WIDTH		9			
#define		HEIGHT		9			

bool	isOpen[WIDTH + 2][HEIGHT + 2];		
bool	isMine[WIDTH + 2][HEIGHT + 2];		
char	nMine[WIDTH + 2][HEIGHT + 2];	
char    posX;
char    posY;

void initBoard();
void drawBoard();
void openBoard(int ,int);
bool clearChecker();


int main()
{
    srand(time(NULL));
    bool isClear = false;
   initBoard();
    while (!isClear) {

        if (_kbhit()) {
            char ch = _getch();
            //if()
            if (ch == 0x4b)(int)posX--; //←
            else if (ch == 0x4d)(int)posX++; //→
            else if (ch == 0x48)(int)posY--; // ↑
            else if (ch == 0x50)(int)posY++; //↓
            if (posX < 0)posX = 0;
            if (posX >= WIDTH)posX = WIDTH-1;
            if (posY < 0)posY = 0;
            if (posY >= HEIGHT)posY = HEIGHT-1;
     
            if (ch == '\r') openBoard((int)posX+1,(int)posY+1);
            drawBoard();
            isClear = clearChecker();
            if (ch == '\r' && isMine[(int)posX + 1][(int)posY + 1]) {
                break;
            }
        }
        
    }

    if (!isClear)cout << "game over";
    else cout << "game clear";

    return 0;
}

void initBoard() {
    posX = 0;
    posY = 0;
    for (int x = 0; x < WIDTH + 2; x++) {
        for (int y = 0;y < HEIGHT + 2;y++) {
            isOpen[x][y] = false;
            isMine[x][y] = false;
            nMine[x][y] = 0;
        }
    }
    int x;
    int y;
    for (int i = 0; i < N_MINE; i++) {
        do {
            x = rand()%WIDTH+1;
            y = rand() % HEIGHT+1;
        } while (isMine[x][y]);
        isMine[x][y] = true;
        nMine[x-1][y-1]++;
        nMine[x-1][y]++;
        nMine[x-1][y+1]++;
        nMine[x][y-1]++;
        nMine[x][y+1]++;
        nMine[x+1][y-1]++;
        nMine[x+1][y]++;
        nMine[x+1][y+1]++;
    }
    drawBoard();
}

void drawBoard(){
    system("cls");
        for (int y = 1;y < HEIGHT + 1;y++) {
            for (int x = 1;x < WIDTH + 1;x++) {
                if ((int)posX + 1 == x && (int)posY + 1 == y) {
                    printf("\033[31m");
                }
                if (!isOpen[x][y]) {
                    cout << "■";
                }else if (isMine[x][y]) {
                    cout << "＊";
                }else if (nMine[x][y] == 0) {
                    cout << "・";
                }else {
                    cout << " " << (int)nMine[x][y];
                }
                if ((int)posX + 1 == x && (int)posY + 1 == y) {
                    printf("\033[0m");
                }
        }
        cout << "\r\n";
    }
}

void openBoard(int x,int y) {
    if (x<1 || x>WIDTH || y<1 || y>HEIGHT)return;
    if (isOpen[x][y]) {
        return;
    }
    isOpen[x][y] = true;
    if (!isMine[x][y] && nMine[x][y] == 0) {
        openBoard(x-1, y-1);
        openBoard(x-1, y);
        openBoard(x-1, y+1);
        openBoard(x, y-1);
        openBoard(x, y+1);
        openBoard(x+1, y-1);
        openBoard(x+1, y);
        openBoard(x+1, y+1);
    }
}

bool clearChecker() {
    for (int y = 1;y < HEIGHT + 1;y++) {
        for (int x = 1;x < WIDTH + 1;x++) {
            if (!isMine[x][y] && !isOpen[x][y]) {
                return false;
            }
        }
    }
    return true;
}


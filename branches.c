#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

void draw(int row, int col, char character);
void creds(int height, int width);
void hidecreds(int height, int width);

int main(){

    int refreshuh, showcreds = 1, width, height;


    srand(time(NULL));


    initscr();
    noecho();
    curs_set(0);

    getmaxyx(stdscr, height, width);
    int middle = width / 2 + 1;

    char branches[height][width];

    mvprintw(height - 4, width - 30, "h to hide this");
    mvprintw(height - 3, width - 30, "towers");
    mvprintw(height - 2, width - 30, "q to quit, n to generate");
    mvprintw(height - 1, width - 30, "created by michael covington");


    int ch;
    while((ch = getch()) != 'q'){
        if(ch == 'n'){
            memset(branches, ' ', sizeof branches);
            int e = rand() % 3;
            switch(e){
                case 0:
                branches[0][middle] = '^';
                break;
                case 1:
                branches[0][middle] = '/';
                break;
                case 2:
                branches[0][middle] = '\\';
                break;
            }
            // branches[0][34] = '^';
            erase();
            refreshuh = 1;
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    int r = rand() % 3;
                    if(j == width - 1){
                        break;
                    }
                    else if(i == height - 1){
                        break;
                    }
                    else if(branches[i][j] == '^'){
                        if(r == 0){
                            branches[i + 1][j - 1] = '/';
                            branches[i + 1][j + 1] = '\\';
                        }
                        else if(r == 1){
                            branches[i + 1][j - 1] = '/';
                            branches[i + 1][j + 1] = '^';
                        }
                        else if(r == 2){
                            branches[i + 1][j - 1] = '^';
                            branches[i + 1][j + 1] = '\\';
                        }
                    }
                    else if(branches[i][j] == '/'){
                        if(r == 1){
                            branches[i + 1][j - 1] = '/';
                        }
                        else if(r == 2){
                            branches[i + 1][j] = '^';
                        }
                        else {
                            branches[i + 1][j] = '\\';
                        }
                    }
                    else if(branches[i][j] == '\\'){
                        if(r == 0){
                            branches[i + 1][j + 1] = '\\';
                        }
                        else if(r == 2){
                            branches[i + 1][j] = '^';
                        }
                        else {
                            branches[i + 1][j] = '/';
                        }
                    }

                }
            }
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(branches[i][j] == '/' || branches[i][j] == '\\' || branches[i][j] == '^'){
                        draw(i, j, branches[i][j]);
                    }
                }
            }
        }

        if(refreshuh){
            refresh();
            refreshuh = 0;
        }
        if(showcreds){
            creds(height, width);
        }
        if(ch == 'h'){
            hidecreds(height, width);
            if(showcreds){
                showcreds = 0;
            }
            else{
                creds(height, width);
                showcreds = 1;
            }

        }


    }
    endwin();

    return 0;
}

void draw(int row, int col, char character){
    mvprintw(row, col, "%c", character);
}

void creds(int height, int width){
    mvprintw(height - 3, width - 30, "towers");
    mvprintw(height - 2, width - 30, "q to quit, n to generate");
    mvprintw(height - 1, width - 30, "created by michael covington");
}
void hidecreds(int height, int width){
    mvprintw(height - 3, width - 30, "              ");
    mvprintw(height - 2, width - 30, "                            ");
    mvprintw(height - 1, width - 30, "                            ");
}

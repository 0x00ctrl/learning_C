#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/*This program will basically read a file and output it like the 'cat' utility in linux or 'read' in windows, so this program is like my own twist at the linux cat utility( although the linux cat utility does much more things and is not this simple) :)*/

//I wrote this code while starting to learn the ncurses library which is used commonly for making TUIs (Terminal User Interfaces)

int main(int argc, char *argv[]){
    int ch, xx,yy,y,x;
    FILE * fp;

    if(argc != 2){
        printf("\n%s <file>", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if(fp ==  NULL){
        perror("\nMusla hogya janu ;p\n");
        exit(1);
    }


    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1) );
    getmaxyx(stdscr,yy, xx );

    while((ch = fgetc(fp)) != EOF){
        getyx(stdscr,y ,x );
        if(y == yy-1){  // if space in terminal window is limited then print the rest on new page
            attron(A_BLINK);
            printw("<<  Press Any Key  >>");
            attroff(A_BLINK);
            getch();
            clear();
            move(0,0);
        }

        attron(A_BOLD);
        printw("%c",ch); //will print the output of file in bold
  
        refresh(); //this finally prints on the screen
        attroff(A_BOLD)
    }
    attroff(COLOR_PAIR(1) );
    attron(A_BLINK); //cool blinkin effectt
    printw("\n << The End >>");
    attroff(A_BLINK);

    getch();
    endwin();
    fclose(fp);


    return 0;


}

//The blinking effect didn't work for me in alacritty, but it worked completey fine in kitty, terminator,konsole and you can check in others too.

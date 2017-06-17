//
//  main.cpp
//  Pongs
//
//  Created by Oskar Domingos on 28.03.2017.
//  Copyright © 2017 Oskar Domingos. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void render_board(char **board, int board_height, int board_width) {
    for (int x = 0; x < board_height; x++) {
        for (int y = 0; y < board_width; y++) {
            //ustaw ramki tablicy
            if (x == 0 || x == board_height - 1) {
                board[x][y] = 'X';
            }
            else if (y == 0 || y == board_width - 1) {
                board[x][y] = 'X';
            }
            else {
                board[x][y] = ' ';
            }
        }
    }
}
//function draws board
//takse three arguments
void draw_board(int width, int height, char **board) {
    //draw board depend on the width and height arguments
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            cout << board[x][y];
        }
        cout << '\n';
    }
};
//function add, update players position and print players
//it takes four arguments
void add_players_on_board( char **board, int board_height, int board_width, int *player_coords) {
    
    //draw player from start to end position
    for (int i = player_coords[0] - 1; i <= player_coords[1] - 1; i++) {
        board[i][2] = '|';
        board[i][board_width - 3] = '|';
    }
}
//function that is responsible for moving players
void make_move(int *player_coords, int board_width, int board_height) {
    int move = getchar();
    if (move == 119 && player_coords[0] > 2) {
        //return displacement of the player
        //-1 because it move player to one place up in board array
        player_coords[0] -= 1;
        player_coords[1] -= 1;
    }
    else if (move == 115 && player_coords[1] < board_height - 2){
        //reutrn displacement of the player
        //-1 because it move player to one place down in board array
        player_coords[0] += 1;
        player_coords[1] += 1;
    }
}
//function that is responsible for moving ball
void move_ball(char **board, int board_height, int board_width, int *ball_coords, int *movementX, int *movementY) {
    //update ball position
    ball_coords[0] += *movementX;
    ball_coords[1] += *movementY;
    board[ball_coords[0]][ball_coords[1]] = 'o';
}
//function that checks collision
void world_collide(int *ball_coords, int *player_coords, int board_height, int board_width, int *movementX, int *movementY) {
    //if ball hits in top boreder
    if(ball_coords[0] == 1) {
        *movementX = 1;
    }
    //else if ball hits in bottom border
    else if (ball_coords[0] == board_height - 2) {
        *movementX = -1;
    }
    //if ball hits left border you are loser
    if (ball_coords[1] == 0) {
        cout << "Przegrana" << endl;
    }
    //else if ball hits right border you are winner
    else if (ball_coords[1] == board_width - 1) {
        cout << "Wygrana" << endl;
    }
}

void check_collision(int *ball_coords, int *player_coords, int *movement, int board_width) {
    if ((ball_coords[1] == 3 && ball_coords[0] >= player_coords[0] && ball_coords[0] <= player_coords[1]) || (ball_coords[1] == board_width - 5 && ball_coords[0] >= player_coords[0] && ball_coords[0] <= player_coords[1])) {
        cout << "Kolizja z paletka" << endl;
        *movement = -1 * *movement;
    }
}

//function
void update_board(int board_height, int board_width, char **board, int *ball_coords, int *player_coords, int *movementX, int *movementY) {
    //set blank board and allow to draw new player position
    render_board(board, board_height, board_width);
    //check that ball collide with borders
    world_collide(ball_coords, player_coords, board_height, board_width, movementX, movementY);
    check_collision(ball_coords, player_coords, movementY, board_width);
    //make player move
    make_move(player_coords, board_width, board_height);
    //add player to the starting position
    add_players_on_board(board, board_height, board_width, player_coords);
    //move ball
    move_ball(board, board_height, board_width, ball_coords, movementX, movementY);
    //draw board
    draw_board(100, 30, board);
}

//main function
int main() {
    
    //width and height of the board
    int board_height = 30, board_width = 100;
    //ball coords
    int ball_coords[2] = {14, 49};
    //player coords
    int player_coords[2] = {(board_height / 2) - 2, (board_height / 2) + 2};
    
    //initialize board as a dynamic 2d array
    char **board = new char *[board_height];
    
    for (int i = 0; i < board_height; i++) {
        board[i] = new char[board_width];
    }
    
    int ball_movementX = 1;
    int ball_movementY = 1;
    
    while(true) {
        //raw mode
        system("stty raw");
        update_board(board_height, board_width, board, ball_coords, player_coords, &ball_movementX, &ball_movementY);
    }
    return 0;
}

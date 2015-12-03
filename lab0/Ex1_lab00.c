#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char a[5][5];
int f[5][5];

int main(){
    int T;
    scanf("%d", &T);
    
    for (int condition = 1; condition <= T; condition++) {
        bool empty = false;
        
        for (int i = 0; i < 4; i++) {
            scanf("%s", a[i]);
            for (int j = 0; j < 4; j++)
                if (a[i][j] == 'T') f[i][j] = 2;
                else if (a[i][j] == 'X') f[i][j] = 1;
                else if (a[i][j] == 'O') f[i][j] = 3;
                else {
                    f[i][j] = 0;
                    empty = true;
                }
        }
        
        //winner: false=X, true=O
        //temp and draw are used for detecting a draw
        bool winner, temp, draw = true;
        //check horizontally
        for (int i = 0; i < 4; i++) {
            temp = true;
            for (int j = 0; j < 4; j++)
                if (f[i][j] > 2 || f[i][j]==0) temp = false;
            if (temp) { winner = false; draw = false; } // X wins
            
            temp = true;
            for (int j = 0; j < 4; j++)
                if (f[i][j] < 2) temp = false;
            if (temp) { winner = true; draw = false; } // O wins
        }
        
        //check vertically
        for (int j = 0; j < 4; j++) {
            temp = true;
            for (int i = 0; i < 4; i++)
                if (f[i][j] > 2 || f[i][j]==0) temp = false;
            if (temp) { winner = false; draw = false; } // X wins
            
            temp = true;
            for (int i = 0; i < 4; i++)
                if (f[i][j] < 2) temp = false;
            if (temp) { winner = true; draw = false; } // O wins
        }
        
        //check diagonally, upper-leftmost to lower-rightmost
        temp = true;
        for (int i = 0; i < 4; i++)
            if (f[i][i] >2 || f[i][i]==0) temp = false;
        if (temp) { winner = false; draw = false; } // X wins
        
        temp = true;
        for (int i = 0; i < 4; i++)
            if (f[i][i] < 2) temp = false;
        if (temp) { winner = true; draw = false; } // O wins
        
        //check diagonally, upper-rightmost to lower-leftmost
        temp = true;
        for (int i = 0; i < 4; i++)
            if (f[i][3-i] >2 || f[i][3-i]==0) temp = false;
        if (temp) { winner = false; draw = false; } // X wins
        
        temp = true;
        for (int i = 0; i < 4; i++)
            if (f[i][3-i] < 2) temp = false;
        if (temp) { winner = true; draw = false; } // O wins
        
        printf("Case #%d: ", condition);
        if (!winner && !draw) printf("X won\n");
        else if (winner && !draw) printf("O won\n");
        else if (empty) printf("Game has not completed\n");
        else printf("Draw\n");
    }
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
typedef struct {
   int x;
   int y;
} Coords;

int totalRows, totalColumns, wordLength;
char grid[100][100], word[100];
 
bool isWaldorfHere(Coords coords) {
    int totalDirections = 8;
    int xDirections[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int yDirections[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for(int i = 0; i < totalDirections; i++) {
        int rowTest = coords.x, columnTest = coords.y, currentCharacter;
        for(currentCharacter = 0; currentCharacter < wordLength; currentCharacter++) {
            if(rowTest >= totalRows || rowTest < 0 || columnTest >= totalColumns || columnTest < 0) break; // break if on an edge case
            if(tolower(grid[rowTest][columnTest]) != tolower(word[currentCharacter])) break; // break if the same character is found
            rowTest += xDirections[i], columnTest += yDirections[i]; //change the direction, since the character is not the same
        }
        if(currentCharacter == wordLength) return true; //the entire string was matched for this direction :)
    }
    return false; //no match found after exhausting all possible directions
}
 
Coords findWaldorf() {
    Coords coords;
    for(coords.x = 0; coords.x < totalRows; coords.x++)
        for(coords.y = 0; coords.y < totalColumns; coords.y++) {
            if(isWaldorfHere(coords))
                return coords;
        }
}
 
int main() {
    int numberOfCases, totalWordsToFind;
    scanf("%d", &numberOfCases);
    for(int currentCase = 0; currentCase < numberOfCases; currentCase++) {
        if(currentCase != 0) printf("\n");
 
        scanf("%d %d\n", &totalRows, &totalColumns);
        for(int currentLine = 0; currentLine < totalRows; currentLine++)
            scanf("%s", grid[currentLine]);
        scanf("%d\n", &totalWordsToFind);
        for(int currentWord = 0; currentWord < totalWordsToFind; currentWord++) {
            scanf("%s", word);
            wordLength = strlen(word);
 
            Coords coords = findWaldorf();
            printf("%d %d\n", coords.x + 1, coords.y + 1);
        }
    }
}
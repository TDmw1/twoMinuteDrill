#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    char team[50];
    int score;
    int time_remaining;  // Player's remaining time in seconds
    int down;            // Current down (1st, 2nd, 3rd, 4th)
    int distance_to_first; // Distance to the first down
    int field_position;  // Player's current position on the field (yard line)
} Player;

// Function declarations for player-related operations
Player createPlayer();
void updatePlayer(Player *player, int yardage, int timeSpent);

#endif

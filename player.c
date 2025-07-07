#include "player.h"

Player createPlayer() {
    Player player;
    player.score = 0;
    player.time_remaining = 120; // 2-minute drill
    player.down = 1;
    player.distance_to_first = 10;
    player.field_position = 25; // Start at own 25-yard line
    return player;
}

void updatePlayer(Player *player, int yardage, int timeSpent) {
    player->field_position += yardage; // Update the player's field position
    player->time_remaining -= timeSpent; // Deduct time spent for the play

    if (yardage >= player->distance_to_first) {
        player->distance_to_first = 10; // Reset the distance to the first down
        player->down = 1; // Reset to 1st down after moving the chains
    } else {
        player->distance_to_first -= yardage; // Update remaining distance to first down
        player->down++; // Move to the next down
    }
}

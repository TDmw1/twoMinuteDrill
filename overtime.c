#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "overtime.h"


// Handles the overtime decision logic
void handleOvertimeScenario(Player *player) {
    int timeLeft = player->time_remaining;
    int chance;

    //relies on time left in game
    
    if (timeLeft > 59) {
        chance = 40;  // 40% OT, 60% opponent scores
    } else if (timeLeft >= 45) {
        chance = 65;  // 65% OT, 35% opponent scores
    } else if (timeLeft >= 30) {
        chance = 80;  // 80% OT, 20% opponent scores
    } else if (timeLeft >= 15) {
        chance = 90;  // 90% OT, 10% opponent scores
    } else {
        handleOvertime();  // Automatically goes to OT if <= 14 seconds
        return;
    }

    int roll = rand() % 100;  // Generate a random number between 0 and 99
    if (roll < chance) {
        printf("\nThe game is tied at the end of regulation. Heading to overtime!\n");
        handleOvertime();
    } else {
        printf("\nYou left too much time on the clock and the opponent scores in the final seconds. Unfortunately, you have lost the game.\n");
    }
}

// Simplified overtime simulator logic
void handleOvertime() {
    printf("\nOvertime begins! A coin flip will decide the outcome of the game!...\n");
    
    srand(time(NULL)); // Seed the random number generator
    if (rand() % 2 == 0) {
        printf("\nCongratulations! Your offense scored a touchdown to win the game in overtime!\n");
    } else {
        printf("\nUnfortunately, your defense couldn't get a stop and you have lost the game in overtime.\n");
    }
}



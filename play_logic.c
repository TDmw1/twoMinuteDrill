#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "play_logic.h"
#include "player.h"

// Function prototypes for internal use
int calculateOutcome(PlayType play, DefensiveLook defense, int *yardage, int *timeSpent);

// Prompt for play selection with input validation
PlayType promptPlay() {
    int choice;
    char buffer[100];
    while (1) { //using infinite while loop
        printf("\nSelect a play:\n1. Run\n2. Quick Pass\n3. Deep Pass\n4. Field Goal\n");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &choice) == 1 && choice >= 1 && choice <= 4) {
            break;
        }
        printf("Invalid input! Please select a valid play.\n");
    }
    switch (choice) { //Using switch instead of if else statements for simplicity
        case 1: return RUN;
        case 2: return QUICK_PASS;
        case 3: return DEEP_PASS;
        case 4: return FIELD_GOAL;
        default: return RUN; // Should not occur
    }
}

// Generate a defensive look (Blitz or Prevent)
DefensiveLook generateDefensiveLook() {
    return (rand() % 2 == 0) ? BLITZ : PREVENT;
}

// Execute the play logic
int executePlay(PlayType play, DefensiveLook defense, Player *player, int *yardage, int *timeSpent) {
    if (!calculateOutcome(play, defense, yardage, timeSpent)) {
        printf("\nInterception! Game over.\n");
        player->time_remaining = 0; // End the game
        return 0; // Indicate interception (play failed)
    }
    return 1; // Indicate play succeeded
}

// Calculate the outcome of the play based on play chances depending on defensive look and selected play
int calculateOutcome(PlayType play, DefensiveLook defense, int *yardage, int *timeSpent) {
    int outcome = rand() % 100; // Generate a random number between 0 and 99

    //this is the play logic, this can be tweaked later
    
    if (play == RUN) {
        if (defense == BLITZ) {
            if (outcome < 55) { // Tackled for a loss
                *yardage = -(rand() % 5 + 1); // Loss of 1-5 yards
                *timeSpent = rand() % 11 + 15; // 15-25 seconds
            } else if (outcome < 90) { // Short run
                *yardage = rand() % 6; // Gain of 0-5 yards
                *timeSpent = rand() % 21 + 10; // 10-30 seconds
            } else { // Long run
                *yardage = rand() % 75 + 25; // Gain of 25-99 yards
                *timeSpent = rand() % 16 + 15; // 15-30 seconds
            }
        } else { // Prevent or Bluff Blitz
            if (outcome < 15) { // Tackled for a loss
                *yardage = -(rand() % 5 + 1); // Loss of 1-5 yards
                *timeSpent = rand() % 11 + 15; // 15-25 seconds
            } else if (outcome < 65) { // Short run
                *yardage = rand() % 6; // Gain of 0-5 yards
                *timeSpent = rand() % 21 + 10; // 10-30 seconds
            } else { // Long run
                *yardage = rand() % 26 + 15; // Gain of 15-40 yards
                *timeSpent = rand() % 16 + 15; // 15-30 seconds
            }
        }
    } else if (play == QUICK_PASS) {
        if (defense == BLITZ) {
            if (outcome < 10) { // Sack
                *yardage = -(rand() % 10 + 1); // Loss of 1-10 yards
                *timeSpent = rand() % 11 + 15; // 15-25 seconds
            } else if (outcome < 65) { // Completion
                *yardage = rand() % 16 + 5; // Gain of 5-20 yards
                *timeSpent = rand() % 6 + 5; // 5-10 seconds
            } else if (outcome < 95) { // Incompletion
                *yardage = 0; // No gain
                *timeSpent = 5; // 5 seconds
            } else { // Interception
                return 0; // Game over
            }
        } else { // Prevent or Bluff Blitz
            if (outcome < 5) { // Sack
                *yardage = -(rand() % 10 + 1); // Loss of 1-10 yards
                *timeSpent = rand() % 6 + 25; // 25-30 seconds
            } else if (outcome < 60) { // Completion
                *yardage = rand() % 11 + 5; // Gain of 5-15 yards
                *timeSpent = rand() % 11 + 5; // 5-15 seconds
            } else if (outcome < 95) { // Incompletion
                *yardage = 0; // No gain
                *timeSpent = 5; // 5 seconds
            } else { // Interception
                return 0; // Game over
            }
        }
    } else if (play == DEEP_PASS) {
        if (defense == BLITZ) {
            if (outcome < 35) { // Sack
                *yardage = -(rand() % 10 + 4); // Loss of 4-13 yards
                *timeSpent = rand() % 6 + 25; // 25-30 seconds
            } else if (outcome < 65) { // Completion
                *yardage = rand() % 80 + 20; // Gain of 20-99 yards
                *timeSpent = rand() % 11 + 20; // 20-30 seconds
            } else if (outcome < 95) { // Incompletion
                *yardage = 0; // No gain
                *timeSpent = rand() % 6 + 5; // 5-10 seconds
            } else { // Interception
                return 0; // Game over
            }
        } else { // Prevent or Bluff Blitz
            if (outcome < 10) { // Sack
                *yardage = -(rand() % 10 + 4); // Loss of 4-13 yards
                *timeSpent = rand() % 6 + 25; // 25-30 seconds
            } else if (outcome < 40) { // Completion
                *yardage = rand() % 21 + 20; // Gain of 20-40 yards
                *timeSpent = rand() % 6 + 20; // 20-25 seconds
            } else if (outcome < 90) { // Incompletion
                *yardage = 0; // No gain
                *timeSpent = rand() % 6 + 5; // 5-10 seconds
            } else { // Interception
                return 0; // Game over
            }
        }
    }

    return 1; // Play executed without interception
}


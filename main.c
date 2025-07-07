#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "play_logic.h"
#include "field_goal.h"
#include "overtime.h"

// Safely reads a line of input, trims any newline, and handles multi-word input
void safeInput(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';  // Remove the newline character
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);  // Clear extra input
        }
    } else {
        printf("Error reading input.\n");
        buffer[0] = '\0';  // Ensure the buffer is empty on failure
    }
}

// Displays the current field position
void displayFieldPosition(int fieldPosition) {
    if (fieldPosition < 50) {
        printf("Ball position: Own %d-yard line\n", fieldPosition);
    } else if (fieldPosition > 50) {
        printf("Ball position: Opponent's %d-yard line\n", 100 - fieldPosition);
    } else {
        printf("Ball position: Midfield (50-yard line)\n");
    }
}


int main() {
    Player player = createPlayer();
    srand(time(NULL));  // RNG

    printf("Welcome to the 2-Minute Drill Football Game!\n");

    printf("Enter your quarterback's name: ");
    safeInput(player.name, sizeof(player.name));

    printf("Enter your team name: ");
    safeInput(player.team, sizeof(player.team));

    printf("\nYou start with the ball at your 25-yard line.\n");
    printf("Your goal is to score a touchdown to win or kick a field goal to send it to overtime.\n");

    while (player.time_remaining > 0) {
        printf("\nDown: %d, Distance to first down: %d yards\n", player.down, player.distance_to_first);
        displayFieldPosition(player.field_position);
        printf("Time left: %d seconds\n", player.time_remaining);

        // Prompt the user for a play
        PlayType play = promptPlay();

        // If the player chooses a field goal, handle it immediately
        if (play == FIELD_GOAL) {
            if (attemptFieldGoal(&player)) {
                printf("\nField goal successful!\n");
                handleOvertimeScenario(&player);  // Trigger overtime scenario
                return 0;
            } else {
                printf("\nMissed field goal! Unfortunately %s, you have lost the game.\n", player.name);
                return 0;
            }
        }

        // Generate a defensive look and show it to the user
        DefensiveLook defense = generateDefensiveLook();
        const char *defenseStr = (defense == BLITZ) ? "Blitz" : "Prevent";
        printf("\nThe defense is showing a %s.\n", defenseStr);

        // Give the user an option to audible
        char audibleChoice[10];
        while (1) {
            printf("Would you like to audible? (y/n): ");
            safeInput(audibleChoice, sizeof(audibleChoice));
            if (audibleChoice[0] == 'y' || audibleChoice[0] == 'Y' || audibleChoice[0] == 'n' || audibleChoice[0] == 'N') {
                break;
            }
            printf("Invalid input! Please enter 'y' or 'n'.\n");
        }

        if (audibleChoice[0] == 'y' || audibleChoice[0] == 'Y') {
            printf("\nChoose your new play:\n1. Run\n2. Quick Pass\n3. Deep Pass\n");
            int audiblePlay;
            while (1) {
                char buffer[10];
                safeInput(buffer, sizeof(buffer));
                if (sscanf(buffer, "%d", &audiblePlay) == 1 && audiblePlay >= 1 && audiblePlay <= 3) {
                    break;
                }
                printf("Invalid choice! Please select a valid play (1-3).\n");
            }

            // Update the play type based on audible
            play = (audiblePlay == 1) ? RUN : (audiblePlay == 2) ? QUICK_PASS : DEEP_PASS;
            printf("\nAudible selected: %s\n", play == RUN ? "Run" : play == QUICK_PASS ? "Quick Pass" : "Deep Pass");
        }

        // Execute the play
        int yardage = 0, timeSpent = 0;
        if (!executePlay(play, defense, &player, &yardage, &timeSpent)) {
            return 0; // Exit the game loop on interception
        }

        const char *playTypeStr = (play == RUN) ? "Run" : (play == QUICK_PASS) ? "Quick pass" : "Deep pass";

        // Check for touchdowns
        int yardsToGoal = 100 - player.field_position;
        if (yardage >= yardsToGoal) {
            printf("\n%s resulted in a %d-yard touchdown!\n", playTypeStr, yardsToGoal);
            printf("\nTouchdown! Congratulations %s, you have won the game!\n", player.name);
            return 0;
        }

        // Handle non-touchdown outcomes
        if (play == QUICK_PASS || play == DEEP_PASS) {
            if (yardage < 0) {
                printf("\nYou were sacked for a %d-yard loss!\n", -yardage);
            } else if (yardage == 0) {
                printf("\nThe pass is incomplete.\n");
            } else {
                printf("\n%s resulted in a %d-yard gain!\n", playTypeStr, yardage);
            }
        } else if (play == RUN) {
            if (yardage >= 0) {
                printf("\n%s resulted in a %d-yard gain!\n", playTypeStr, yardage);
            } else {
                printf("\n%s resulted in a %d-yard loss.\n", playTypeStr, -yardage);
            }
        }

        // Update player stats and game state
        updatePlayer(&player, yardage, timeSpent);

        if (player.down > 4) {
            printf("\nTurnover on downs! Unfortunately %s, you have lost the game.\n", player.name);
            return 0;
        }

        if (player.time_remaining <= 0) {
            printf("\nTime's up! Unfortunately %s, you have lost the game.\n", player.name);
            return 0;
        }
    }

    printf("\nTime's up! Unfortunately %s, you have lost the game.\n", player.name); //should not trigger
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "field_goal.h"

int attemptFieldGoal(Player *player) {
    int distanceToGoal = 100 - player->field_position;
    int fieldGoalLength = distanceToGoal + 17;

    printf("\nAttempting a %d-yard field goal...\n", fieldGoalLength);

    srand(time(NULL));
    int chance = rand() % 100; //predetermined random number generated before field goal logic is applied

    if (fieldGoalLength >= 68) {
        return chance < 1;
    } else if (fieldGoalLength >= 65) {
        return chance < 2;
    } else if (fieldGoalLength >= 60) {
        return chance < 20;
    } else if (fieldGoalLength >= 55) {
        return chance < 40;
    } else if (fieldGoalLength >= 50) {
        return chance < 50;
    } else if (fieldGoalLength >= 40) {
        return chance < 75;
    } else if (fieldGoalLength >= 30) {
        return chance < 95;
    } else {
        return chance < 99;
    }
}

#ifndef PLAY_LOGIC_H
#define PLAY_LOGIC_H

#include "player.h"

//Offensive plays
typedef enum {
    RUN,
    QUICK_PASS,
    DEEP_PASS,
    FIELD_GOAL  // New play type for field goal
} PlayType;

//Defensive Looks
typedef enum {
    BLITZ,
    PREVENT,
    BLUFF_BLITZ  //  Defensive look for Bluff Blitz, Inherently prevent, but user believes it is a blitz
} DefensiveLook;

PlayType promptPlay();  // Function declaration for prompting play
DefensiveLook generateDefensiveLook();  // Function declaration for generating defensive look
int executePlay(PlayType play, DefensiveLook defense, Player *player, int *yardage, int *timeSpent);// Return int and updates time/location

#endif

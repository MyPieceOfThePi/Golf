#ifndef GOLF_H
#define GOLF_H

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cards.h"

#define NUM_PLAYERS 2

struct Player;

typedef enum {
    DRAW_DISCARD,
    DRAW_DECK
} DrawDecision;

typedef enum {
    SWAP,
    DISCARD
} ActionType;

typedef struct {
    Hand selfHand;
    Hand oppHand[NUM_PLAYERS - 1];
} GameView;

typedef struct {
    ActionType actionType;
    int row;
    int col;
} Action;

typedef DrawDecision (*DecideDrawFn)(void *state, const GameView *gv, const Card *discard);
typedef Action (*DecideActionFn)(void *state, const GameView *gv, const Card *drawn);

typedef struct Player{
    DecideDrawFn decideDrawFn;
    DecideActionFn decideActionFn;
    Hand hand;
    void *state;
} Player;

void play(Player players[NUM_PLAYERS]);

#endif
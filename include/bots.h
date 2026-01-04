#ifndef BOTS_H
#define BOTS_H

#include "golf.h"
#include "cards.h"

// Human bot
DrawDecision human_draw(void *state, const GameView *gv, const Card *discard);
Action human_action(void *state, const GameView *gv, const Card *draw);


#endif 
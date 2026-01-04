#include <stdlib.h>
#include <time.h>

#include "golf.h"
#include "cards.h"
#include "bots.h"

int main(){
    srand(time(0));

    Player players[2] = {
    {
        .decideDrawFn = human_draw,
        .decideActionFn = human_action,
        .state = NULL
    },
    {
        .decideDrawFn = human_draw,
        .decideActionFn = human_action,
        .state = NULL
    }
    };

    play(players);
}
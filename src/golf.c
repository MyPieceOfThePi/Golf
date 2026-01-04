#include "golf.h"

struct Player;

void deal_hand(Hand *hand, Deck *deck){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            hand->cards[i][j] = deal_card(deck);
        }
    }
}

void handcpy(Hand *dest, Hand *src){
    memcpy(dest, src, sizeof(Hand));
    for(int j = 0; j < 2; j++){
        for(int i = 0; i < 3; i++){
            if(dest->cards[i][j].shown == false) dest->cards[i][j] = (Card) {0, 0, false};
        }
    }
}

GameView make_game_view(Player players[NUM_PLAYERS], int to_play){
    GameView gv;
    handcpy(&gv.selfHand, &(players[to_play].hand));

    int indx = 0;
    for(int i = 0; i < NUM_PLAYERS; i++){
        if(i == to_play) continue;
        handcpy(&gv.oppHand[indx++], &(players[i].hand));
    }

    return gv;
}

const void print_hand(const Hand *hand, const bool labels){
    if(labels){
        for(int i = 0; i < 3; i++) printf("     %c", 'A' + i);
        printf("\n");
    }
    
    for(int j = 0; j < 2; j++){
        printf("%c ", labels ? '1' + j : ' ');
        for(int i = 0; i < 3; i++){
            print_card(hand->cards[i][j]);
        }
        printf("\n");
    }
}

void print_game(Hand *hand1, Hand *hand2, Card discard, int to_play){
    printf("\033[2J\033[1;1H");
    printf("   Player %i to play\n\n", to_play + 1);
    print_hand(hand2, false);
    printf("\n        ");
    print_card(discard);
    printf("\n\n");
    print_hand(hand1, true);
    printf("\n");
}

bool game_over(Player players[NUM_PLAYERS]){
    for(int i = 0; i < NUM_PLAYERS; i++){
        bool all_shown = true;
        for(int r = 0; r < 2; r++){
            for(int c = 0; c < 3; c++){
                if(!players[i].hand.cards[c][r].shown){
                    all_shown = false;
                    break;
                }
            }
            if(!all_shown) break;
        }
        if(all_shown) return true;
    }
    return false;
}

int scores[14] = {0, 1, -2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 0};
int score(Hand hand){
    int score = 0;
    for(int i = 0; i < 3; i++){
        if(hand.cards[0][i].rank == hand.cards[1][i].rank) continue;
        score += hand.cards[0][i].rank + hand.cards[1][i].rank;
    }
}

void play(Player players[NUM_PLAYERS]){
    Deck deck;
    make_deck(&deck);
    shuffle(&deck);

    Card discard = deal_card(&deck);
    discard.shown = true;

    for(int i = 0; i < NUM_PLAYERS; i++){
        deal_hand(&(players[i].hand), &deck);
    }

    while(!game_over(players)){
        for(int i = 0; i < NUM_PLAYERS; i++){
            print_game(&(players[i].hand), &(players[!i].hand), discard, i);
            GameView gv = make_game_view(players, i);

            DrawDecision drawDecision = players[i].decideDrawFn(players[i].state, &gv, &discard);
            Card draw = drawDecision == DRAW_DISCARD ? discard : deal_card(&deck);
            draw.shown = true;

            Action action = players[i].decideActionFn(players[i].state, &gv, &draw);
            if(action.actionType == DISCARD){
                discard = draw;
                continue;
            }

            discard = players[i].hand.cards[action.col][action.row];
            discard.shown = true;
            players[i].hand.cards[action.col][action.row] = draw;

            if(game_over(players)) break;
        }
    }

    for(int i = 0; i < NUM_PLAYERS; i++){
        for(int r = 0; r < 2; r++){
            for(int c = 0; c < 3; c++){
                players[i].hand.cards[r][c].shown = true;
            }
        }
    }

    print_game(&(players[0].hand), &(players[1].hand), discard, 0);

    int min_indx, min = INT_MAX;
    int scores[NUM_PLAYERS] = {0};
    for(int i = 0; i < NUM_PLAYERS; i++){
        scores[i] = score(players[i].hand);
        printf("Player %d score: %d\n", i + 1, scores[i]);

        if(scores[i] < min){
            min = scores[i];
            min_indx = i;
        }
    }

    printf("Player %d wins!\n", min_indx + 1);
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bots.h"

DrawDecision human_draw(void *state, const GameView *gv, const Card *discard) {
    char choice;
    printf("Draw from deck or discard? (d=deck, x=discard): ");
    while (1) {
        scanf(" %c", &choice);
        if (choice == 'd' || choice == 'D') return DRAW_DECK;
        if (choice == 'x' || choice == 'X') return DRAW_DISCARD;
        printf("Invalid choice, enter d or x: ");
    }
}

Action human_action(void *state, const GameView *gv, const Card *drawn) {
    Action action;
    char input[3];  // two characters + null terminator

    printf("Drawn card: ");
    print_card(*drawn);
    printf("\nEnter cell to swap (A1-C2) or x to discard: ");

    while (1) {
        scanf("%2s", input);  // read up to 2 chars
        if (input[0] == 'x' || input[0] == 'X') {
            action.actionType = DISCARD;
            action.row = 0;  // ignored
            action.col = 0;  // ignored
            return action;
        }

        // Check for valid cell input: first char A-C, second char 1-2
        if ((input[0] >= 'A' && input[0] <= 'C') &&
            (input[1] >= '1' && input[1] <= '2')) {
            action.actionType = SWAP;
            action.col = input[0] - 'A';
            action.row = input[1] - '1';
            return action;
        }

        printf("Invalid input, enter x or a cell (A1-C2): ");
    }
}
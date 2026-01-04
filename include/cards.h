#ifndef CARDS_H
#define CARDS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
    UNDEF,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} Suit;

typedef struct {
    Suit suit;
    int rank;
    bool shown;
} Card;

typedef struct {
    Card cards[52];
    int top;
} Deck;

typedef struct {
    Card cards[3][2];
} Hand;

void make_deck(Deck *deck);
void shuffle(Deck *deck);
Card deal_card(Deck *deck);
void print_card(const Card card);

#endif
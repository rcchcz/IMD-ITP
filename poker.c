#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int suit, value;
} Card;

enum {Clubs, Diamonds, Heart, Spades} suit;

enum {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace} value;

typedef enum {HighCard, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush} PokerHand;

void bubbleSort(Card hand[]) { 
    Card aux; 
    for(int j = 4; j >= 1; j--) { 
        for(int i = 0; i < j; i++) { 
            if(hand[i].value < hand[i+1].value) { 
                aux = hand[i]; 
                hand[i] = hand[i+1]; 
                hand[i+1] = aux; 
            } 
        } 
    } 
}

PokerHand checkHand(Card hand[5]) {
    bubbleSort(hand);

    int mesmoNaipe = 1;
    for(int i = 1; i < 5; i++) {
        if(hand[i].suit != hand[i-1].suit) {
            mesmoNaipe=0;
            break;
        }
    }

    int emSequencia = 1;
    for(int i = 0; i < 4; i++) {
        if(hand[i].value - hand[i+1].value != 1) {
            emSequencia = 0;
            break;
        }
    }

    if(mesmoNaipe && emSequencia) {
        if(hand[0].value == 12) {
            return RoyalFlush;
        } else {
            return StraightFlush;
        }
    }

    if(hand[0].value == hand[3].value || hand[1].value == hand[4].value) {
        return FourOfAKind;
    }

    if((hand[0].value == hand[1].value && hand[2].value == hand[4].value) || (hand[0].value == hand[2].value && hand[3].value == hand[4].value)) {
        return FullHouse;
    }

    if(mesmoNaipe) {
        return Flush;
    }

    if(emSequencia) {
        return Straight;
    }

    for(int i = 0; i < 3; i++) {
        int threeOfAKind = 1;
        for(int j = i + 1; j < 5; j++) {
            if(hand[i].value == hand[j].value && ++threeOfAKind == 3) {
                return ThreeOfAKind;
            }
        }
    }

    for(int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (hand[i].value==hand[j].value) {
                for(int k = 0; i < 4; i++) {
                    for (int l = i + 1; j < 5; j++) {
                        if (hand[i].value != hand[k].value && hand[k].value == hand[l].value) {
                            return TwoPair;
                        }
                    }
                }
                i=5;
                j=5;
                break;
            }
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(hand[i].value == hand[j].value) {
                return Pair;
            }
        }
    } 

    return HighCard;
}

int main() {
    Card hands[][5] = {
        {  // Royal Flush
        { Diamonds, Ace },
        { Diamonds, King },
        { Diamonds, Queen }, 
        { Diamonds, Jack }, 
        { Diamonds, Ten } 
        },
        { // Full house
        { Heart, Jack },   
        { Spades, Jack },   
        { Clubs, Jack },     
        { Spades, Two  },    
        { Heart, Two } 
        },   
        { // Three of a Kind
        { Diamonds, Ten }, 
        { Spades, Seven },  
        { Diamonds, Four },  
        { Spades, Four  },   
        { Heart, Four } 
        },  
        { // Pair
        { Spades, Ace  },  
        { Heart, Jack },    
        { Spades, Jack },    
        { Heart, Seven },    
        { Clubs, Four } 
        },  
        { // High Card (No pair)
        { Clubs, Nine },   
        { Heart, Seven },   
        { Diamonds, Six },   
        { Spades, Four  },   
        { Heart, Two } 
        },   
    };
    Card myCards[5];
    Card oponentCards[5];

    unsigned handIndex;
    scanf("%u", &handIndex);
    for(int i = 0; i < 5; i++) {
        myCards[i] = hands[handIndex][i];
        scanf("%u %u", &oponentCards[i].suit, &oponentCards[i].value);
    }
    PokerHand myHand = checkHand(myCards);
    PokerHand oponentHand = checkHand(oponentCards);
    if (myHand > oponentHand) {
        switch(myHand) {
            case RoyalFlush:
                printf("É... simplesmente não tinha como me bater!\n");
                break;
            case StraightFlush:
            case FourOfAKind:
            case FullHouse:
                printf("Já era! Você não tinha chance!\n");
                break;
            case Flush:
            case Straight:
            case ThreeOfAKind:
                printf("É boy! Quem sabe da próxima vez...\n");
                break;
            default:
                printf("Tive sorte!\n");
        }
    }
    else if (oponentHand > myHand) {
        printf("Não valeu! Cê tá roubando!!!\n");
    }
    else if (myCards[0].value > oponentCards[0].value) {
        printf("Ufa! Por pouco!");
    }
    else {
        printf("Nan!! Bicho melado da gota!\n");
    }
    return 0;
}
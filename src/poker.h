#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

enum Suitmark{
    CLUBS, HEARTS, DIAMONDS, SPADES, NO_SUIT
};

Suitmark intToSuitmark(int val){
    if(val == 0) return Suitmark::CLUBS;
    if(val == 1) return Suitmark::HEARTS;
    if(val == 2) return Suitmark::DIAMONDS;
    if(val == 3) return Suitmark::SPADES;
    return Suitmark::NO_SUIT;
}

enum CardValue{
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, AS, NO_VALUE
};

CardValue intToCardValue(int val){
    if(val == 0) return CardValue::TWO;
    if(val == 1) return CardValue::THREE;
    if(val == 2) return CardValue::FOUR;
    if(val == 3) return CardValue::FIVE;
    if(val == 4) return CardValue::SIX;
    if(val == 5) return CardValue::SEVEN;
    if(val == 6) return CardValue::EIGHT;
    if(val == 7) return CardValue::NINE;
    if(val == 8) return CardValue::TEN;
    if(val == 9) return CardValue::JACK;
    if(val == 10) return CardValue::QUEEN;
    if(val == 11) return CardValue::KING;
    if(val == 12) return CardValue::AS;
    return CardValue::NO_VALUE;
}

struct Card{
    Suitmark suitmark;
    CardValue value;

    std::string str(){
        
    }
};

class Poker{
public:
    Poker(int _noDecks, int _players): noDecks(_noDecks), players(_players) {
        generateDeck();
        shuffleDeck();
        it = 0;
    }

    void generateDeck(){
        for(int k = 0; k<noDecks; k++){
            for(int i = 0; i<4; i++){
                for(int j = 0; j<13; j++){
                    deck.push_back(Card{.suitmark=intToSuitmark(i), .value=intToCardValue(j)});
                }
            }
        }
    }

    void shuffleDeck(){
        std::random_shuffle(deck.begin(), deck.end());
        it = 0;
    }

    Card consumeCard(int amm = 1){
        if(it >= deck.size()) 
            return Card{.suitmark=Suitmark::NO_SUIT, .value=CardValue::NO_VALUE};
        
        Card out = deck[it];
        amm += it;
        return out;
    }

    void resetGame(){
        for(Player& p : players){
            p.clearCards();
        }

        for(int i = 0; i<2; i++){
            for(Player& p : players){
                p.drawCard(consumeCard());
            }
        }
    }
private:
    int noDecks; 
    std::vector<Card> deck;
    std::vector<Player> players;
    int it;
};

class Player{
public:
    void clearCards(){
        holdingCards.clear();
    }

    void drawCard(Card card){
        holdingCards.push_back(card);
    }

    void displayCards(){
        for(Card& c : holdingCards){
            std::cout << c.str() << std::endl;
        }
    }
private:
    std::vector<Card> holdingCards;
};

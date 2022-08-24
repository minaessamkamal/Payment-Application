#include "Card/card.h"
#include "Terminal/terminal.h"
#include "stdio.h"
int main() {
    ST_cardData_t card;
    ST_terminalData_t term;
   // uint8_t x =getCardExpiryDate(&card);
   // uint8_t y = getCardPAN(&card);
   // uint8_t z =getCardHolderName(&card);

   // float a = setMaxAmount(&term);
   // float b = isBelowMaxAmount(&term);
   //float c = getTransactionAmount(&term);
   //float d = getTransactionDate(&term);
   float e = isCardExpired(card, term);
    //printf("%d %d %d", x,y,z);
return 0;
}

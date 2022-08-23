#include "Types/Types.h"
#include "Card/card.h"
#include "stdio.h"
int main() {
    ST_cardData_t card;
    uint8_t x =getCardExpiryDate(&card);
    uint8_t y = getCardPAN(&card);
    uint8_t z =getCardHolderName(&card);
    printf("%d %d %d", x,y,z);
return 0;
}

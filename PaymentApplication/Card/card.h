/********************************************
* *File Name:    Card.c                      *
* *Created by:   Mina Essam                  *
* *Date:         08/20/2022                  *
* *Version:      V01                         *
 ********************************************/

#ifndef CARD_H
#define CARD_H
#include "../Types/Types.h"
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;
typedef enum EN_cardError_t
{
    Card_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
typedef enum cardNameValidation{
    emptyName =0,
    minNameChar = 20,
    maxNameChar = 24
}cardNameValidation;

typedef enum cardPANValidation{
    emptyPAN =0,
    minPANNumber = 16,
    maxPANNumber = 19
}cardPANValidation;

typedef enum cardExpiryDateValidation{
    emptyDate,

}dateValidation;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
#endif

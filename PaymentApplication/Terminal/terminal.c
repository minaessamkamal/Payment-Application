
#include "../Types/Types.h"
#include "../Card/card.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string.h"
#include "terminal.h"
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
  static float amount;
    EN_terminalError_t isMaxEqualZero;
    printf("Please enter Maximum transaction amount: \t");
    scanf("%f", &amount);
    if(amount <= 0){
        isMaxEqualZero = INVALID_MAX_AMOUNT;
        printf("\nmaximum transaction amount should not less than or equal to zero \n");
    }
    else {
        isMaxEqualZero = Terminal_OK;
        printf("\nSUCCESS!\n");
    }
    /*the if condition */
    if(isMaxEqualZero == Terminal_OK)
    {
        termData->maxTransAmount = amount;
        printf("\nWe have a new Max transaction %f", termData->maxTransAmount);
    }
    else{
        /* do nothing*/
    }
    return isMaxEqualZero;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
uint8_t isBelow;
if(termData->transAmount > termData->maxTransAmount)
{
    isBelow =EXCEED_MAX_AMOUNT;
    printf("You entered an amount that exceed max terminal amount which is %f", termData->maxTransAmount);
}
else{
    isBelow = Terminal_OK;
    printf("amount is valid \n");
}
return isBelow;
}


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    EN_terminalError_t isValidDate= Terminal_OK;
    uint8_t TransactionDate[10];

    printf("OS time is %s\n", _strdate(TransactionDate));
    TransactionDate[8] = TransactionDate[6];
    TransactionDate[9] = TransactionDate[7];
    TransactionDate[6] = '2';
    TransactionDate[7] = '0';
    strcpy(termData->transactionDate,TransactionDate);
    printf("the new format is %s", termData->transactionDate);
    return isValidDate;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
uint32_t cardValue, terminalValue;
getCardExpiryDate(&cardData);
cardValue = atoi(cardData.cardExpirationDate);
sscanf(cardData.cardExpirationDate,"%d %d %d");
}
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){

}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float transactionAmount;
    EN_terminalError_t transactionResponse;
    printf("Please enter the amount you need to Withdraw from your account: \t");
    scanf("%f", &transactionAmount);
    termData->transAmount = transactionAmount;
    if(transactionAmount <= 0){
        transactionResponse = INVALID_AMOUNT;
        printf("The amount you can withdraw should be bigger than zero\n");
    }
    else{
        transactionResponse = Terminal_OK;
    }
    if(transactionResponse == Terminal_OK) {
        printf("The amount you withdraw from your account is %f", termData->transAmount);

    }
    return transactionResponse;
}
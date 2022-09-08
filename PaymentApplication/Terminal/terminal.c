/********************************************
* *File Name:    Terminal.c                  *
* *Created by:   Mina Essam                  *
* *Date:         08/20/2022                  *
* *Version:      V01                         *
 ********************************************/

/**                         Includes                            *****/

#include "../Types/Types.h"
#include "../Card/card.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "string.h"
#include "terminal.h"
/**                         End of Includes                     ******/

/***************************************************************************
 * Function : Set Maximum Amount per transaction where amount is > 0   *****
 * Input    :   Terminal structure                                     *****
 * Output   :  0 Set Max Successfully otherwise print error message    *****
 **************************************************************************/
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
      //  printf("\nSUCCESS!\n");
    }
    /*the if condition */
    if(isMaxEqualZero == Terminal_OK)
    {
        termData->maxTransAmount = amount;
        printf("\nMax transaction Amount:  %f\n", termData->maxTransAmount);
    }
    else{
        /* do nothing*/
    }
    return isMaxEqualZero;
}

/***************************************************************************
 * Function :   Check if withdrawn amount <= MAX transaction amount     *****
 * Input    :   Terminal structure                                      *****
 * Output   :  0 Amount is correct otherwise print error message        *****
 ****************************************************************************/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
uint8_t isBelow;
if(termData->transAmount > termData->maxTransAmount)
{
    isBelow =EXCEED_MAX_AMOUNT;
    printf("You entered an amount that exceed max terminal amount which is %f\n", termData->maxTransAmount);
    exit(0);
}
else{
    isBelow = Terminal_OK;
    printf("Amount is valid \n");
}
return isBelow;
}

/***************************************************************************
 * Function :   Get system date for the transaction                     *****
 * Input    :   Terminal structure                                      *****
 * Output   :   System date                                             *****
 ****************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    EN_terminalError_t isValidDate= Terminal_OK;
    uint8_t TransDate[10]={0};
    strcpy_s(TransDate,sizeof(TransDate)/ sizeof(TransDate[0]), _strdate(TransDate));
   // printf("OS time is %s\n", TransDate);
    TransDate[8] = TransDate[6];
    TransDate[9] = TransDate[7];
    TransDate[6] = '2';
    TransDate[7] = '0';
    //printf("NEEEE %s \n", TransDate);
    strcpy_s(termData->transactionDate, sizeof(termData->transactionDate)/ sizeof(termData->transactionDate[0]),TransDate);
    printf("the Transaction Date ... %s\n", termData->transactionDate);
    return isValidDate;
}

/***************************************************************************
 * Function :   This function is to check system date with card expiry date
 *              If the card expiry year is bigger than system date or
 *              if the card expiry year is same year but with bigger month
 *              the card is valid
 *              Otherwise system year is bigger than card expiry or month of system
 *              is bigger return an error
 *
 * Input    :   Terminal structure pointer and card structure pointer                                    *****
 * Output   :   System date                                             *****
 ****************************************************************************/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    EN_terminalError_t isExpired;
    uint8_t cDate, transDate;
    uint8_t CADAte[3],tranDate[5];
    /** the following function will copy the date stored in card date into local
     * variable CAD_DATe
     * Month*/
  //  printf("We will copy for the  terminal date: %s \n", termData.transactionDate);
  //  printf("We will copy for the date that %s \n", cardData.cardExpirationDate);

    strncpy_s(CADAte, sizeof(CADAte)/ sizeof(CADAte[0]),cardData.cardExpirationDate+3,2);
    /**this function to take year of trans date*/

    strncpy_s(tranDate, sizeof(tranDate)/ sizeof(tranDate[0]), termData.transactionDate+8,2);

    cDate = atoi(CADAte);
    transDate = atoi(tranDate);

  //  printf("cDATE = %d\n",cDate);
//    printf("transDate = %d\n",transDate);
//    printf("tranDate = %s\n",termData.transactionDate+8);

    if(cDate > transDate){
        isExpired = Terminal_OK;
        printf("Card is Valid\n");
    }
    else if( cDate < transDate){
        isExpired =EXPIRED_CARD;
        printf("Card is Expired Transaction Declined ...\n");
        exit(0);
    }
    else{
     //   printf("we are here \n");
        strncpy_s(CADAte, sizeof(CADAte)/ sizeof(CADAte[0]),cardData.cardExpirationDate,2);
        /*this function to take month of trans date*/
        strncpy_s(tranDate, sizeof(tranDate)/ sizeof(tranDate[0]), termData.transactionDate,2);
        cDate = atoi(CADAte);
        transDate = atoi(tranDate);
        if(cDate >= transDate)
        {
            isExpired = Terminal_OK;
            printf("card month is valid \n");
        }
        else
        {
            isExpired = EXPIRED_CARD;
            printf("Card is expired as of month Transaction Declined \n");
            exit(0);
        }
    }
return isExpired;
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
        printf("The amount you withdraw from your account is %f\n", termData->transAmount);

    }
    return transactionResponse;
}
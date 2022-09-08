/********************************************
 *File Name:    card.c                      *
 *Created by:   Mina Essam                  *
 *Date:         08/20/2022                  *
 *Version:      V01                         *
 ********************************************/

/*****                      Includes                                */
#include "../Types/Types.h"
#include "stdio.h"
#include "string.h"
#include "card.h"
#include <stdlib.h>
/**                         End of Includes                         */

/********************************************************************
 * Function is to check if given name is meet name rules or not *****
 * Input:   structure pointer                                   *****
 * Output:  0 if card name is correct 1 if card name is wrong   *****
 ********************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    EN_cardError_t result ;
    uint8_t name[25] = {0}, nameLength;
    printf("Please enter card holder name:\t");
    scanf("%[^\n]s", name);
    nameLength = strlen(name);
    //printf("length of the chars you entered %d \t", nameLength);
    if(nameLength == emptyName){
        printf("You enter an empty name\n");
        result = WRONG_NAME;
    }
    else if(nameLength <minNameChar ||nameLength > maxNameChar){
        printf("Minimum name length is 24 and you enter a %d name's length\n", nameLength );
        result = WRONG_NAME;
    }
    else{
     //   printf("You enter Valid Name:\n");
        result = Card_OK;
    }
    if(result == Card_OK) {
        strcpy_s(cardData->cardHolderName, sizeof(cardData->cardHolderName)/ sizeof(cardData->cardHolderName[0]),name);
        printf("\nWe are Saving: '%s' in our DB....\n", cardData->cardHolderName);
    }
    else{
        printf("Failed to save the value in our records as it didn't meet name rules!");

        exit(0);
    }
    return result;
}

/*****************************************************************************
 * Function is to check if card PAN is meet account rules or not            ***
 * Input: structure pointer                                                 ***
 * Output: Card_OK if card PAN is correct Wrong_PAN if card PAN is incorrect **
 ************************************************************************************/
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    EN_cardError_t PANValidation ;
    uint8_t PAN[20]={0}, panLength;
    printf("Please enter PAN Number:\t");
    scanf("%[^\n]s", PAN);
    panLength = strlen(PAN);
if(panLength == emptyPAN)
{
    PANValidation = WRONG_PAN;
    printf("You enter an empty PAN number \n %d", panLength);

}
else if(panLength <minPANNumber || panLength > maxPANNumber){
    PANValidation = WRONG_PAN;
    printf("\n Minimum name length is 16 and you enter PAN \t %s and it' length \t %d\n",PAN,panLength);

}
else{
    PANValidation = Card_OK;
   // printf("\nYou have entered a correct PAN:\t %s %d\n", PAN, panLength);
}

if(PANValidation == Card_OK)
{
    strcpy_s(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber)/ sizeof(cardData->primaryAccountNumber[0]),PAN);
    printf("We are Saving: '%s' in our DB....\n", cardData->primaryAccountNumber);
}
else{
    printf("Failed to save the value in our records as PAN number doesn't meet PAN rules \n");
    exit(0);
}
return PANValidation;
}
/**
 * Function is to check whether the expiry date is written in the right format
 * (MM/YY) or not
 * Input structure pointer
 * Output Card_OK if date is written in (MM/YY) otherwise return Wrong_Expiry_date
 * **********************************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    EN_cardError_t DateValidation = Card_OK;
    uint8_t date[6]={0}, dateLen;
    printf("Please enter Card Expiry Date of the card in format (MM/YY) \t");
    scanf("%[^\n]s", date);
    dateLen = strlen(date);
    //condition to check if the user entered an empty date
    if(dateLen ==emptyDate) {
        printf("You enter no date\n");
        DateValidation = WRONG_EXP_DATE;
    }
    else if(date[0] != '0' && date[0] != '1'){
        DateValidation =WRONG_EXP_DATE;
        printf("You enter a wrong month\n");
    } else if(date[0] =='0'){
        if(date[1] =='0' || date[1]>'9' ){
            DateValidation = WRONG_EXP_DATE;
            printf("Wrong Format\n");
        }
        else{
            DateValidation = Card_OK;
            printf("Success\n");
        }
    }
    else if (date[0] =='1'){
        if(date[1] >'2') {
            DateValidation = WRONG_EXP_DATE;
            printf("Wrong format \n");
        }
    }
    else if(date[2] == '/')
    {
        DateValidation = Card_OK;
        printf("OK!");
    }
    else if((date[3] >='0' && date[3] <='9') && (date[4] >='0' && date[4] <='9'))
    {
        DateValidation = Card_OK;
                printf("Year Ok\n");
    }
    else if(dateLen > 5)
    {
        DateValidation = WRONG_EXP_DATE;
        printf("Date Format length is exceed maximum date length which is 5\n");
    }
    if(DateValidation == Card_OK){
        strcpy_s(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate)/ sizeof(cardData->cardExpirationDate[0]), date);
        printf("The date you entered is %s\n", cardData->cardExpirationDate);
    }
    else{
        /** do nothing       */
    }
return DateValidation;
}
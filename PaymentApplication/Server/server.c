/*
/ Created by minae on 8/20/2022.
*/
#include "server.h"
#include <stdio.h>
#include <string.h>
extern ST_accountsDB_t Accounts[255];
extern ST_transaction_t transactionDetails[255];
static uint32_t sequenceNumber    = 1000;
static uint8_t transactionCounter = 0;
static int16_t DBCounter = 0;

/*search function in DB accounts to search for a given PAN number and return
 * the index of the found PAN number*/
int32_t searchInDB(ST_cardData_t *cData){
    printf("we are in search \n");
    int32_t index, subIndex, result = -1, isMatched = -1;
    for(index =0; index<255; index++)
    {
        for(subIndex =0; subIndex < strlen(cData->primaryAccountNumber); subIndex++) {

            if (cData->primaryAccountNumber[subIndex] == Accounts[index].primaryAccountNumber[subIndex])
            {

                    isMatched = 1;
            }
            else
            {
                isMatched = -1;
                break;
            }

        }
        if(isMatched == 1){
            result = index;
            break;
        }
    }
    return result;
}
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    EN_serverError_t isTransactionSaved;
    if(transactionCounter == 255)
    {
        isTransactionSaved = SAVING_FAILED;
        printf("Exceeded transaction count limits \n");
    }
    else{

        transactionDetails[transactionCounter]= *transData;
        transactionDetails[transactionCounter].transactionSequenceNumber = sequenceNumber;
        transactionCounter++;
        sequenceNumber++;
        isTransactionSaved = OK;
        printf("transaction saved successfully  and it's sequence numer is  %d \n",sequenceNumber);
    }
return isTransactionSaved;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){

    EN_serverError_t isAvailableBalance = LOW_BALANCE;
    if(termData->transAmount > Accounts[DBCounter].balance){
        isAvailableBalance = LOW_BALANCE;
        printf("Low Balance \n");
    }
    else
    {
        isAvailableBalance = OK;
        printf("Balance is OK!\n");
    }
    return isAvailableBalance;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    EN_serverError_t isValidAccount;
    DBCounter =searchInDB(cardData);
   if(DBCounter == -1)
   {
       isValidAccount = ACCOUNT_NOT_FOUND;
        printf("account not found\n");
    }
    else
    {
        isValidAccount = OK;
    }
    return isValidAccount;
}

EN_transStat_t receiveTransactionData(ST_transaction_t *transData) {
    EN_transStat_t isSavedTransaction = APPROVED;
    printf("we are ready \n");
    if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){
        isSavedTransaction = DECLINED_STOLEN_CARD;
        printf("here 1 \n");
    }
    else if(isAmountAvailable(&transData->terminalData) == LOW_BALANCE){
        isSavedTransaction = DECLINED_INSUFFICIENT_FUND;
        printf("here 2 \n");
    }
    else if(saveTransaction(transData)== SAVING_FAILED ){
        isSavedTransaction = INTERNAL_SERVER_ERROR;
        printf("here 3 \n");
    }
    else{
        Accounts[DBCounter].balance -= transData->terminalData.transAmount;
        isSavedTransaction= APPROVED;
        printf("here\n");
        printf("The new balance after withdrawing is %f \n", Accounts[DBCounter].balance);
    }

return isSavedTransaction;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    uint8_t i;
    EN_serverError_t isFound;
    printf("We are in receive transaction \n");
    for(i = 0; i <255;i++)
    {
        if(transactionSequenceNumber == transactionDetails[i].transactionSequenceNumber)
        {
            *transData = transactionDetails[i];
            isFound = OK;
        }
        else {
            isFound = TRANSACTION_NOT_FOUND;
            break;
        }
    }

    printf("Final username is %s \n", transData->cardHolderData.cardHolderName);
    printf("Transaction Date %s\n", transData->terminalData.transactionDate);
    printf("Card Expiry Date %s \n", transData->cardHolderData.cardExpirationDate);
    printf("Withdrawn Amount %d \n", transData ->terminalData.transAmount);
    return isFound;
}

/********************************************
 *File Name:    App.c                       *
 *Created by:   Mina Essam                  *
 *Date:         08/20/2022                  *
 *Version:      V01                         *
 ********************************************/


/**                  Includes                                    */
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "stdio.h"
#include "app.h"
/**                  End of Includes                             */

/**     Global and static variables declaration                 **/
static ST_cardData_t cardData;
static ST_terminalData_t termData;
extern ST_accountsDB_t Accounts[255];
static ST_transaction_t transactionDetails;
static uint32_t transaction_Number = 0;
/**     End of Global and static variables declarations         **/

void appStart(void){
    getCardHolderName(&cardData);
    getchar();
    getCardPAN(&cardData);
    getchar();
   getTransactionDate(&termData);
   getCardExpiryDate(&cardData);
    isCardExpired(cardData, termData);
    setMaxAmount(&termData);
    getTransactionAmount(&termData);
    isCardExpired(cardData, termData);
    isBelowMaxAmount(&termData);
    ST_transaction_t serverData ={cardData, termData};
    receiveTransactionData(&serverData);
    transaction_Number = transactionNumber();
    getTransaction(transaction_Number, &transactionDetails);
}

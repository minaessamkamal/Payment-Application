/********************************************
 *File Name:    Server.h                    *
 *Created by:   Mina Essam                  *
 *Date:         08/20/2022                  *
 *Version:      V01                         *
 ********************************************/

/*******                     Header Guard                   *****/
#ifndef SERVER_H
#define SERVER_H
#include "../Terminal/terminal.h"
/*******                    End of Header Guard            ******/

/****                   Enums Definition                   ******/
typedef enum EN_transState_t
{

    APPROVED, DECLINED_INSUFFICIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;


typedef enum EN_serverError_t
{
    OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t;

/******             End of Enum Definition                  *****/
/****************************************************************/

/******             Struct Definition                       *****/

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transStat_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;


typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
/****               End of Struct Definition                    ******/

/****                   Function Prototypes                     ******/
EN_transStat_t receiveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
uint32_t transactionNumber(void);
/****                   End of Struct Definition                ******/
#endif //SERVER_H
/****                   End of Server file                      ******/
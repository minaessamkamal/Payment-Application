/********************************************
 *File Name:    App.c                      **
 *Created by:   Mina Essam                  *
 *Date:         08/20/2022                  *
 *Version:      V01                         *
 ********************************************/

/*******         Includes          **********/

#include "Server/server.h"
#include "../PaymentApplication/Application/app.h"
#include <string.h>
#include <stdio.h>

/**             Global Variables             **/
ST_accountsDB_t Accounts[255];
ST_transaction_t transactionDetails[255];

/**             End of Global Variables      **/

int main() {
    /**                       DB records  *****/

    Accounts[0].balance = 15000;
    memcpy(Accounts[0].primaryAccountNumber,"A151011121314152",sizeof(Accounts[0].primaryAccountNumber)/ sizeof(Accounts[0].primaryAccountNumber[0]));
    Accounts[1].balance = 1000000;
    memcpy(Accounts[1].primaryAccountNumber,"A151011121314153",sizeof(Accounts[1].primaryAccountNumber)/ sizeof(Accounts[1].primaryAccountNumber[1]));
    Accounts[2].balance = 2000;
    memcpy(Accounts[2].primaryAccountNumber,"A151011121314157",sizeof(Accounts[2].primaryAccountNumber)/ sizeof(Accounts[2].primaryAccountNumber[2]));

    appStart();
    return 0;
}

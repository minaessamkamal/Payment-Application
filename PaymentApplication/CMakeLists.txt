cmake_minimum_required(VERSION 3.23)
project(PaymentApplication C)

set(CMAKE_C_STANDARD 99)

add_executable(PaymentApplication main.c Application/app.h Application/app.c Card/card.h Terminal/terminal.h Terminal/terminal.c Server/server.c Server/server.h Card/card.c Types/Types.h)

cmake_minimum_required(VERSION 3.21)
project(ChatBots C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatBots main.c new.h new.c message.h message.c
            user.c user.h bot.c bot.h boy.c boy.h)

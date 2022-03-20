cmake_minimum_required(VERSION 3.21)
project(ChatBots C)

set(CMAKE_C_STANDARD 11)

add_executable(ChatBots main.c New.h New.c DArray.c DArray.h ChatArray.h ChatArray.c Parser.h Parser.c
        User.c User.h Boy.c Boy.h Girl.c Girl.h RichBoy.c RichBoy.h CowardGirl.h CowardGirl.c)

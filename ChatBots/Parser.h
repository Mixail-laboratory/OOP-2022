#ifndef CHATBOTS_PARSER_H
#define CHATBOTS_PARSER_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "User.h"
#include "Boy.h"
#include "Girl.h"
#include "RichBoy.h"
#include "CowardGirl.h"
#include "New.h"
#include "ChatArray.h"

void* parse_file(const char* file);

void* parse_line(const char* line);
#endif //CHATBOTS_PARSER_H

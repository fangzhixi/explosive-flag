//
// Created by 95100 on 2024/5/15.
//

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <stdlib.h>
#include <setjmp.h>
#include <malloc.h>

#define EMPTY 0

#define MIN_PRINT_ASCII 0x7 //ASCII最小值
#define MAX_PRINT_ASCII 0x7e //ASCII最大值
#define MAX_FLAG_LENGTH 0xff //碰撞flag最大长度

#define GENERATE_STATUS_CLEAR_VALUE 0 //清空记录flag结果
#define GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE 1 //未找到当前值
#define GENERATE_STATUS_IS_MATCH_CURRENT_VALUE 2 //已找到当前值
#define GENERATE_STATUS_START GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE //碰撞开始(等价于未找到值)
#define GENERATE_STATUS_FINISH 3 //碰撞结束

#define GENERATE_MATCH_NO_PARSE_LOOP_INDEX (-1) //不分析for循环中flag正在比对的位置

#ifndef EXPLOSIVE_FLAG_EXPLOSIVE_FLAG_H
#define EXPLOSIVE_FLAG_EXPLOSIVE_FLAG_H

#endif //EXPLOSIVE_FLAG_EXPLOSIVE_FLAG_H

extern jmp_buf jump_buf;

char *GenerateFlagStart();

char *GenerateFlag(int match_status, int match_index);

int GenerateStrcmp(char *str1, char *str2);

bool GenerateFlagPrefix(char *prefix_str);

bool GenerateFlagSuffix(char *suffix_str);
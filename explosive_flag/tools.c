#include"explosive_flag.h"

int flag_max_len = MAX_FLAG_LENGTH;
char flag_str[MAX_FLAG_LENGTH] = {0};
char flag_result[MAX_FLAG_LENGTH] = {0};
int flag_prefix_len = UNKNOWN;
int flag_suffix_index = UNKNOWN;
bool is_add_prefix_index = false; //是否已经添加前缀下标补偿

jmp_buf jump_buf;

/*
 * 爆破强制跳转
 * 需搭配 setjmp(jump_buf); 标记跳转节点
 * 为确保服务健壮性, 跳转前需确认是否已经标记跳转节点
 * */
void generateJump() {
    size_t buf_len = sizeof(jump_buf) / sizeof(jump_buf[0]);
    for (int i = 0; i < buf_len; i++) {
        if (jump_buf[i].Part[0] != EMPTY || jump_buf[i].Part[1] != EMPTY) {
            break;
        }
        if (i == buf_len - 1) {
            printf("\ntips: 貌似忘记设置返回点了\n");
            printf("tips: 请使用 setjmp(jump_buf); 标记跳转点位\n");
            printf("tips: setjmp(jump_buf); 推荐设置在程序输入flag附近, 请检查\n");
            exit(0);
        }
    }
    longjmp(jump_buf, 1);
}

char *generateStrcpy(char *dest, char *source) {
    strcpy(dest, source);
    if (flag_suffix_index == UNKNOWN) {
        return flag_result;
    }
    strcpy(&dest[flag_suffix_index], &source[flag_suffix_index]);
    return flag_result;
}

/*
 * 碰撞flag
 * 使用场景为flag与目标数组逐一比对验证
 * 原理为flag单个字符按顺序逐一碰撞, 实现效率最优
 * 需要断点回溯逻辑放置setjmp(jump_buf);实现断点回溯
 *
 * param setjmp(jump_buf); 断点回溯
 * param match_status 配对状态值
 *      GENERATE_STATUS_CLEAR_VALUE 清空记录flag结果
 *      GENERATE_STATUS_START 碰撞开始
 *      GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE 未找到当前值
 *      GENERATE_STATUS_IS_MATCH_CURRENT_VALUE 已找到当前值
 *      GENERATE_STATUS_FINISH 碰撞结束
 * param match_index 当前flag比对位置
 *      GENERATE_MATCH_NO_PARSE_LOOP_INDEX 不分析for循环中flag正在比对的位置
 * */
char *GenerateFlag(int match_status, int match_index) {
    int flag_match_len = (int) strlen(flag_str);
    if (flag_match_len == 0) {
        flag_str[0] = MIN_PRINT_ASCII;
        generateStrcpy(flag_result, flag_str);
        return flag_result;
    }

    if (flag_match_len > flag_max_len || flag_str[flag_max_len - 1] == 0x7f) {
        printf("\n测试用例结束，未找到目标flag: %d\n", flag_match_len);
        exit(0);
    }

    char ascii;
    switch (match_status) {
        case GENERATE_STATUS_IS_MATCH_CURRENT_VALUE:
            //flag碰撞数组位置补偿
            if (is_add_prefix_index || (flag_prefix_len != UNKNOWN && match_index < flag_prefix_len)) {
                match_index += flag_prefix_len;
                is_add_prefix_index = true;
            }
            if (match_index >= 0 && flag_match_len != match_index + 1) {
                return flag_result;
            }
            if (flag_match_len == MAX_FLAG_LENGTH) {
                printf("\n测试用例存在缺陷, 请检查放置GENERATE_STATUS_IS_MATCH_CURRENT_VALUE位置是否正确\n");
            }
            printf("%s\n", flag_str);
            flag_str[flag_match_len] = MIN_PRINT_ASCII;
            generateStrcpy(flag_result, flag_str);
            return flag_result;

        case GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE:
            //递归终点
            if (flag_str[0] == MAX_PRINT_ASCII) {
                printf("\n测试用例存在缺陷, 第%d位已完成全部字符遍历,但未碰撞出目标值\n", flag_match_len);
                printf("结果: %s\n", flag_str);
                printf("请检查放置goto语句[setjmp(jump_buf);]是否正确, 或本题不适用单字符碰撞\n");
                exit(0);
            }
            for (int i = 1; i < flag_match_len; i++) {
                ascii = flag_str[i];
                //递归起点
                if (ascii == MAX_PRINT_ASCII) {
                    //回滚，假设上一个字符正确值不唯一
                    flag_match_len = i;
                    flag_str[flag_match_len - 1] += 1;
                    flag_str[flag_match_len] = '\0';//清空当前字符
                    generateStrcpy(flag_result, flag_str);
                    generateJump();
                }
            }

            flag_str[flag_match_len - 1] += 1;
            generateStrcpy(flag_result, flag_str);
            generateJump();

        case GENERATE_STATUS_FINISH:
            printf("\n碰撞结束!\n结果: %s\n", flag_str);
            return flag_result;

        case GENERATE_STATUS_CLEAR_VALUE:
            memset(flag_str, '\0', MAX_FLAG_LENGTH);
            generateStrcpy(flag_result, flag_str);
            return flag_result;

        default:
            printf("\n未知状态码: %d\n", match_status);
            exit(0);
    }
}

/*
 * 增加flag前缀
 * 手动增加前缀不影响flag碰撞结果,可以重复追加前缀
 * */
bool GenerateFlagPrefix(char *prefix_str) {
    if (strlen(flag_str) + strlen(prefix_str) > MAX_FLAG_LENGTH / 2) {
        printf("flag前缀超出额定长度");
        return false;
    }

    flag_prefix_len = (int) strlen(prefix_str);
    for (int i = (int) strlen(flag_str) - 1; i >= 0; i--) {
        flag_str[i + flag_prefix_len] = flag_str[i];
    }

    for (int i = 0; i < flag_prefix_len; i++) {
        flag_str[i] = prefix_str[i];
    }
    generateStrcpy(flag_result, flag_str);
    return true;
}

/*
 * 增加flag后缀
 * 手动增加后缀不影响flag碰撞结果
 * */
bool GenerateFlagSuffix(char *suffix_str, int suffix_index) {
    int suffix_str_len = (int) strlen(suffix_str);
    if (suffix_index + suffix_str_len > MAX_FLAG_LENGTH) {
        printf("flag后缀超出额定长度, 放弃追加后缀\n");
        return false;
    }

    flag_suffix_index = suffix_index;
    for (int i = 0; i < suffix_str_len; i++) {
        flag_str[flag_suffix_index + i] = suffix_str[i];
    }
    generateStrcpy(flag_result, flag_str);
    return true;
}

/*
 *  验证碰撞flag值，平替strcmp
 *  需要与断点回溯配合使用 setjmp(jump_buf);
 *  此方法对三种可能性进行处理
 *      ①当前字符与目标值不一致时，提供新的字符并强制跳转到标记点参与新一次碰撞
 *      ②当前字符与目标值一致时，记录当前字符并寻找下一个字符
 *      ③碰撞字符串与目标值完成一致时，碰撞成功，输出结果
 *  param generate_str 碰撞字符串
 *  param target_str 目标字符串(flag等)
 * */
int GenerateStrcmp(char *generate_str, char *target_str) {
    int comparison_value = 0;//误差值
    int str_len_max = (int) strlen(target_str);
    int str_len_min = (int) strlen(generate_str);

    if ((int) strlen(generate_str) > str_len_max) {
        str_len_min = (int) strlen(target_str);
        str_len_max = (int) strlen(generate_str);
    }

    if (str_len_min == 0) {
        printf("\ntips: 碰撞字符串可能未设置正确, 推荐设置在程序输入flag处, 请检查\n");
        system("PAUSE");
    }

    for (int i = 0; i < str_len_max; i++) {
        if (generate_str[i] == target_str[i]) {
            //碰撞成功
            GenerateFlag(GENERATE_STATUS_IS_MATCH_CURRENT_VALUE, i);
        } else {
            //碰撞失败
            GenerateFlag(GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE, i);
            comparison_value = -1;
        }
    }
    GenerateFlag(GENERATE_STATUS_FINISH, GENERATE_MATCH_NO_PARSE_LOOP_INDEX);
    return comparison_value;
}

/*
 * 碰撞flag
 * 使用场景为flag与目标数组逐一比对验证
 * 原理为flag单个字符按顺序逐一碰撞, 实现效率最优
 * 需要断点回溯逻辑放置setjmp(jump_buf);实现断点回溯
 * */
char *GenerateFlagStart() {
    return GenerateFlag(GENERATE_STATUS_START, GENERATE_MATCH_NO_PARSE_LOOP_INDEX);
}
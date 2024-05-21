#include"explosive_flag.h"

int func() {
    int result; // eax
    char *v1; // [esp+14h] [ebp-44h]
    char *input_str; // [esp+24h] [ebp-34h] BYREF
    char v3[29]; // [esp+3Bh] [ebp-1Dh] BYREF
    int i = 0;
    strcpy(v3, "Qsw3sj_lz4_Ujw@l");
    printf("Please input:");
//    scanf("%s", input_str);
    input_str = GenerateFlagStart();
    GenerateFlagPrefix("ACTF{");
    GenerateFlagSuffix("}", 22);
    setjmp(jump_buf);
    result = input_str[0];
    if (input_str[0] == 'A') {
        result = input_str[1];
        if (input_str[1] == 'C') {
            result = input_str[2];
            if (input_str[2] == 'T') {
                result = input_str[3];
                if (input_str[3] == 'F') {
                    result = input_str[4];
                    if (input_str[4] == '{') {
                        result = input_str[22];
                        if (input_str[22] == '}') {
                            v1 = &input_str[5];
                            i = 0;
                            while (i <= 15) {
                                if (*(v1 + i) > '@' && *(v1 + i) <= 'Z')// 大写
                                    *(v1 + i) = (*(v1 + i) - 51) % 26 + 'A';
                                if (*(v1 + i) > '`' && *(v1 + i) <= 'z')// 小写
                                    *(v1 + i) = (*(v1 + i) - 79) % 26 + 'a';
                                ++i;
                            }
                            i = 0;
                            while (i <= 15) {
                                result = v3[i];
                                if (*(v1 + i) != result) {
                                    GenerateFlag(GENERATE_STATUS_IS_NOT_MATCH_CURRENT_VALUE, i);
                                } else {
                                    GenerateFlag(GENERATE_STATUS_IS_MATCH_CURRENT_VALUE, i);
                                }
                                ++i;
                            }
                            GenerateFlag(GENERATE_STATUS_FINISH, GENERATE_MATCH_NO_PARSE_LOOP_INDEX);
                            return printf("You are correct!");
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    func();
}
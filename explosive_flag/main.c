#include"explosive_flag.h"

unsigned __int64 Decry() {
    char v1; // [rsp+Fh] [rbp-51h]
    int v2; // [rsp+10h] [rbp-50h]
    int v3; // [rsp+14h] [rbp-4Ch]
    int i; // [rsp+18h] [rbp-48h]
    int v5; // [rsp+1Ch] [rbp-44h]
    char src[8] = "SLCDN"; // [rsp+20h] [rbp-40h] BYREF
    __int64 v7; // [rsp+28h] [rbp-38h]
    int v8; // [rsp+30h] [rbp-30h]
    char v9[16] = "wodah"; // [rsp+40h] [rbp-20h] BYREF
    int v10; // [rsp+50h] [rbp-10h]
    unsigned __int64 v11; // [rsp+58h] [rbp-8h]

    v7 = 0LL;
    v8 = 0;
    v10 = 0;
    char text[100] = "killshadow";
    char key[100] = "ADSFKNDCLS";


    v2 = 0;
    v3 = 0;
//    getchar();
    v5 = strlen(key);
    for (i = 0; i < v5; ++i) {
        if (key[v3 % v5] > '@' && key[v3 % v5] <= 'Z')
            key[i] = key[v3 % v5] + ' ';
        ++v3;
    }
    printf("Please input your flag:\n");
    char *str2 = GenerateFlagStart();
    setjmp(jump_buf);
    for (i = 0; i < strlen(str2); i++) {
        v1 = str2[i];
        if (v1 == ' ') {
            ++v2;
        } else {
            if (v1 <= '`' || v1 > 'z') {
                if (v1 > '@' && v1 <= 'Z') {
                    str2[i] = (v1 - 39 - key[i % v5] + 'a') % 26 + 'a';
                    ++v3;
                }
            } else {
                str2[i] = (v1 - 39 - key[i % v5] + 'a') % 26 + 'a';
                ++v3;
            }
            if (!(v3 % v5))
                putchar(' ');
        }
    }

    if (!GenerateStrcmp(text, str2))
        puts("Congratulation!\n");
    else
        puts("Try again!\n");
    return 0;
}

int __cdecl main(int argc, const char **argv, const char **envp) {
    Decry();
    return 0;
}
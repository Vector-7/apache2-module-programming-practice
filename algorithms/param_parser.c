#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PARAM_MAX 100

char*** get_args(char* raw)
// raw data를 key-value 스타일로 변형하는 함수
{
    int i;

    // 동적할당
    //char*** res = NULL;
    
    char*** res = (char***)malloc(sizeof(char**) * PARAM_MAX);
    for(int i = 0; i < PARAM_MAX; i++)
    {
        res[i] = (char**)malloc(sizeof(char*) * 2);
        res[i][0] = res[i][1] = NULL;
    }

    int len = strlen(raw);
    
    int l = 0, r = 0, k = 0;
    do
    {
        if(r == len-1 || raw[r] == '&')
        {
            // 구분선에 들어간 경우
            if(r < len-1) raw[r] = '\0';
            res[k][0] = &raw[l];

            while(raw[l] != '=') l++;
            raw[l++] = '\0';
            res[k++][1] = &raw[l];
            l = r + 1;
        }
        r++;

    } while(k < PARAM_MAX && r < len);
    return res;
}

int main(void)
{
    char s[128];
    scanf("%s", s);

    char*** res = get_args(s);
    int i = 0;
    for(i=0; res[i][0]; i++)
    {
        printf("%s %s\n", res[i][0], res[i][1]);
    }
}
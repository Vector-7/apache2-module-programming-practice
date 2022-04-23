#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include <string.h>
#include <stdlib.h>

#define PARAM_MAX 10

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

/* The sample content handler */
static int method_get_handler(request_rec *r)
{
    if (strcmp(r->handler, "method_get")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    if (!r->header_only)
    {
        char* data = r->args;   // url에 붙어있는 parameter를 불러온다.
        if(!data) ap_rprintf(r, "%s\n", "No Args have.");   // 없는 경우
        else
        {
            char*** args = get_args(data);
            int i = 0;
            if(args)
            {
                for(i = 0; args[i][0]; i++)
                {
                    // 파라미터 내용 출력
                    ap_rprintf(r, "%s -> %s\n", args[i][0], args[i][1]);
                    free(args[i]);  // 동적 할당 해제
                }
                free(args); // 동적 할당 해제
            }
        }
    }
    return OK;
}

static void method_get_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(method_get_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA method_get_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    method_get_register_hooks  /* register hooks                      */
};


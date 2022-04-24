#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#define PARAM_MAX 2

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
static int web_api_handler(request_rec *r)
{
    if (strcmp(r->handler, "web_api")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    if (!r->header_only)
    {
        char* raw_params = r->args;
        if(!raw_params) ap_rprintf(r, "%d", 0);
        else
        {
            // 파라미터 파싱
            char*** args = get_args(raw_params);
            int inputs[2], i;

            // 파싱된 데이터를 int로 전환
            for(i=0; args[i][0] && i < 2; i++)
                inputs[i] = atoi(args[i][1]);
            
            if(i<2) ap_rprintf(r, "%s:%d", "error", 1); // 파싱된 데이터가 2개 이하일 경우
            else ap_rprintf(r, "%s:%d", "ok", inputs[0]+inputs[1]);
        }
    }
    return OK;
}

static void web_api_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(web_api_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA web_api_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    web_api_register_hooks  /* register hooks                      */
};


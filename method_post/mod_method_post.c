#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "apr_strings.h"

typedef struct {
    const char *key;
    const char *value;
} keyValuePair;

keyValuePair *readPost(request_rec *r) {
    apr_array_header_t *pairs = NULL;
    apr_off_t len;
    apr_size_t size;
    int res;
    int i = 0;
    char *buffer;
    keyValuePair *kvp;

    res = ap_parse_form_data(r, NULL, &pairs, -1, HUGE_STRING_LEN);
    if (res != OK || !pairs) return NULL; /* Return NULL if we failed or if there are is no POST data */
    kvp = apr_pcalloc(r->pool, sizeof(keyValuePair) * (pairs->nelts + 1));
    while (pairs && !apr_is_empty_array(pairs)) {
        ap_form_pair_t *pair = (ap_form_pair_t *) apr_array_pop(pairs);
        apr_brigade_length(pair->value, 1, &len);
        size = (apr_size_t) len;
        buffer = apr_palloc(r->pool, size + 1);
        apr_brigade_flatten(pair->value, buffer, &size);
        buffer[len] = 0;
        kvp[i].key = apr_pstrdup(r->pool, pair->name);
        kvp[i].value = buffer;
        i++;
    }
    return kvp;
}

/* The sample content handler */
static int method_post_handler(request_rec *r)
{
    if (strcmp(r->handler, "method_post")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    if (!r->header_only)
    {
        keyValuePair* form = readPost(r); // 데이터 얻기
        if(form)
        {
            // formData를 발견하는 경우만
            register int i;
            for(i=0; &form[i]; i++)
            {
                if(form[i].key && form[i].value)
                    ap_rprintf(r, "Key: %s -> Value: %s\n", form[i].key, form[i].value);
                else if (!(form[i].key && form[i].value)) break;
            }
        }
    }
    return OK;
}

static void method_post_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(method_post_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA method_post_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    method_post_register_hooks  /* register hooks                      */
};


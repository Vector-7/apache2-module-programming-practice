#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

/* The sample content handler */
static int get_header_handler(request_rec *r)
{
    if (strcmp(r->handler, "get_header")) {
        return DECLINED;
    }
    r->content_type = "text/html";      

    if (!r->header_only)
    {   
        const char* val = apr_table_get(r->headers_in, "key");
        if(!val) ap_rprintf(r, "%s\n", "No Header");
        else ap_rprintf(r, "Value: %s\n", val);
    }
    return OK;
}

static void get_header_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(get_header_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA get_header_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    get_header_register_hooks  /* register hooks                      */
};


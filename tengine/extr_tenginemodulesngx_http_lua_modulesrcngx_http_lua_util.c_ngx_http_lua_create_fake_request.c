#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int keep_alive_n; scalar_t__ content_length_n; } ;
struct TYPE_7__ {int count; int discard_body; int /*<<< orphan*/  http_state; scalar_t__ subrequests; scalar_t__ uri_changes; TYPE_1__ headers_in; int /*<<< orphan*/  method; struct TYPE_7__* main; int /*<<< orphan*/  signature; TYPE_3__* connection; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_cleanup_t ;
struct TYPE_8__ {TYPE_2__* data; int /*<<< orphan*/  pool; int /*<<< orphan*/  requests; } ;
typedef  TYPE_3__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_MAX_SUBREQUESTS ; 
 scalar_t__ NGX_HTTP_MAX_URI_CHANGES ; 
 int /*<<< orphan*/  NGX_HTTP_MODULE ; 
 int /*<<< orphan*/  NGX_HTTP_PROCESS_REQUEST_STATE ; 
 int /*<<< orphan*/  NGX_HTTP_UNKNOWN ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int ngx_http_max_module ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_http_request_t *
ngx_http_lua_create_fake_request(ngx_connection_t *c)
{
    ngx_http_request_t      *r;

    r = ngx_pcalloc(c->pool, sizeof(ngx_http_request_t));
    if (r == NULL) {
        return NULL;
    }

    c->requests++;

    r->pool = c->pool;

    dd("r pool allocated: %d", (int) (sizeof(ngx_http_lua_ctx_t)
       + sizeof(void *) * ngx_http_max_module + sizeof(ngx_http_cleanup_t)));

#if 0
    hc = ngx_pcalloc(c->pool, sizeof(ngx_http_connection_t));
    if (hc == NULL) {
        goto failed;
    }

    r->header_in = c->buffer;
    r->header_end = c->buffer->start;

    if (ngx_list_init(&r->headers_out.headers, r->pool, 0,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        goto failed;
    }

    if (ngx_list_init(&r->headers_in.headers, r->pool, 0,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        goto failed;
    }
#endif

    r->ctx = ngx_pcalloc(r->pool, sizeof(void *) * ngx_http_max_module);
    if (r->ctx == NULL) {
        return NULL;
    }

#if 0
    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    r->variables = ngx_pcalloc(r->pool, cmcf->variables.nelts
                               * sizeof(ngx_http_variable_value_t));
    if (r->variables == NULL) {
        goto failed;
    }
#endif

    r->connection = c;

    r->headers_in.content_length_n = 0;
    c->data = r;
#if 0
    hc->request = r;
    r->http_connection = hc;
#endif
    r->signature = NGX_HTTP_MODULE;
    r->main = r;
    r->count = 1;

    r->method = NGX_HTTP_UNKNOWN;

    r->headers_in.keep_alive_n = -1;
    r->uri_changes = NGX_HTTP_MAX_URI_CHANGES + 1;
    r->subrequests = NGX_HTTP_MAX_SUBREQUESTS + 1;

    r->http_state = NGX_HTTP_PROCESS_REQUEST_STATE;
    r->discard_body = 1;

    dd("created fake request %p", r);

    return r;
}
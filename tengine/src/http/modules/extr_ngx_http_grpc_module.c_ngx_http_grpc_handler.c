#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {scalar_t__ tag; } ;
struct TYPE_17__ {int ssl; TYPE_6__* input_filter_ctx; int /*<<< orphan*/  input_filter; int /*<<< orphan*/  input_filter_init; int /*<<< orphan*/  finalize_request; int /*<<< orphan*/  abort_request; int /*<<< orphan*/  process_header; int /*<<< orphan*/  reinit_request; int /*<<< orphan*/  create_request; TYPE_2__* conf; TYPE_1__ output; int /*<<< orphan*/  schema; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
struct TYPE_18__ {int request_body_no_buffering; int /*<<< orphan*/  pool; TYPE_3__* upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_16__ {int /*<<< orphan*/ * ssl; } ;
struct TYPE_19__ {TYPE_2__ upstream; } ;
typedef  TYPE_5__ ngx_http_grpc_loc_conf_t ;
struct TYPE_20__ {TYPE_4__* request; } ;
typedef  TYPE_6__ ngx_http_grpc_ctx_t ;
typedef  scalar_t__ ngx_buf_tag_t ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 scalar_t__ NGX_OK ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_grpc_abort_request ; 
 int /*<<< orphan*/  ngx_http_grpc_create_request ; 
 int /*<<< orphan*/  ngx_http_grpc_filter ; 
 int /*<<< orphan*/  ngx_http_grpc_filter_init ; 
 int /*<<< orphan*/  ngx_http_grpc_finalize_request ; 
 int /*<<< orphan*/  ngx_http_grpc_module ; 
 int /*<<< orphan*/  ngx_http_grpc_process_header ; 
 int /*<<< orphan*/  ngx_http_grpc_reinit_request ; 
 scalar_t__ ngx_http_read_client_request_body (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_create (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_init ; 
 TYPE_6__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_handler(ngx_http_request_t *r)
{
    ngx_int_t                  rc;
    ngx_http_upstream_t       *u;
    ngx_http_grpc_ctx_t       *ctx;
    ngx_http_grpc_loc_conf_t  *glcf;

    if (ngx_http_upstream_create(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    glcf = ngx_http_get_module_loc_conf(r, ngx_http_grpc_module);

    u = r->upstream;

#if (NGX_HTTP_SSL)
    u->ssl = (glcf->upstream.ssl != NULL);

    if (u->ssl) {
        ngx_str_set(&u->schema, "grpcs://");

    } else {
        ngx_str_set(&u->schema, "grpc://");
    }
#else
    ngx_str_set(&u->schema, "grpc://");
#endif

    u->output.tag = (ngx_buf_tag_t) &ngx_http_grpc_module;

    u->conf = &glcf->upstream;

    u->create_request = ngx_http_grpc_create_request;
    u->reinit_request = ngx_http_grpc_reinit_request;
    u->process_header = ngx_http_grpc_process_header;
    u->abort_request = ngx_http_grpc_abort_request;
    u->finalize_request = ngx_http_grpc_finalize_request;

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_grpc_ctx_t));
    if (ctx == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ctx->request = r;

    ngx_http_set_ctx(r, ctx, ngx_http_grpc_module);

    u->input_filter_init = ngx_http_grpc_filter_init;
    u->input_filter = ngx_http_grpc_filter;
    u->input_filter_ctx = ctx;

    r->request_body_no_buffering = 1;

    rc = ngx_http_read_client_request_body(r, ngx_http_upstream_init);

    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}
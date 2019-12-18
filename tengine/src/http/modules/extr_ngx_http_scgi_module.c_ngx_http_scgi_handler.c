#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_19__ {scalar_t__ tag; } ;
struct TYPE_23__ {TYPE_2__* pipe; int /*<<< orphan*/  buffering; int /*<<< orphan*/  finalize_request; int /*<<< orphan*/  abort_request; int /*<<< orphan*/  process_header; int /*<<< orphan*/  reinit_request; int /*<<< orphan*/  create_request; int /*<<< orphan*/  create_key; int /*<<< orphan*/ * caches; TYPE_3__* conf; TYPE_1__ output; int /*<<< orphan*/  schema; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_status_t ;
struct TYPE_24__ {int /*<<< orphan*/  caches; } ;
typedef  TYPE_6__ ngx_http_scgi_main_conf_t ;
struct TYPE_21__ {scalar_t__ pass_request_body; int /*<<< orphan*/  request_buffering; int /*<<< orphan*/  buffering; } ;
struct TYPE_25__ {TYPE_3__ upstream; scalar_t__ scgi_lengths; } ;
typedef  TYPE_7__ ngx_http_scgi_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  chunked; } ;
struct TYPE_26__ {int request_body_no_buffering; TYPE_4__ headers_in; int /*<<< orphan*/  pool; scalar_t__ state; TYPE_5__* upstream; } ;
typedef  TYPE_8__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_event_pipe_t ;
typedef  scalar_t__ ngx_buf_tag_t ;
struct TYPE_20__ {TYPE_8__* input_ctx; int /*<<< orphan*/  input_filter; } ;

/* Variables and functions */
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_event_pipe_copy_input_filter ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_read_client_request_body (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_scgi_abort_request ; 
 int /*<<< orphan*/  ngx_http_scgi_create_key ; 
 int /*<<< orphan*/  ngx_http_scgi_create_request ; 
 scalar_t__ ngx_http_scgi_eval (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_scgi_finalize_request ; 
 int /*<<< orphan*/  ngx_http_scgi_module ; 
 int /*<<< orphan*/  ngx_http_scgi_process_status_line ; 
 int /*<<< orphan*/  ngx_http_scgi_reinit_request ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_create (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_init ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_scgi_handler(ngx_http_request_t *r)
{
    ngx_int_t                   rc;
    ngx_http_status_t          *status;
    ngx_http_upstream_t        *u;
    ngx_http_scgi_loc_conf_t   *scf;
#if (NGX_HTTP_CACHE)
    ngx_http_scgi_main_conf_t  *smcf;
#endif

    if (ngx_http_upstream_create(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    status = ngx_pcalloc(r->pool, sizeof(ngx_http_status_t));
    if (status == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    ngx_http_set_ctx(r, status, ngx_http_scgi_module);

    scf = ngx_http_get_module_loc_conf(r, ngx_http_scgi_module);

    if (scf->scgi_lengths) {
        if (ngx_http_scgi_eval(r, scf) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    u = r->upstream;

    ngx_str_set(&u->schema, "scgi://");
    u->output.tag = (ngx_buf_tag_t) &ngx_http_scgi_module;

    u->conf = &scf->upstream;

#if (NGX_HTTP_CACHE)
    smcf = ngx_http_get_module_main_conf(r, ngx_http_scgi_module);

    u->caches = &smcf->caches;
    u->create_key = ngx_http_scgi_create_key;
#endif

    u->create_request = ngx_http_scgi_create_request;
    u->reinit_request = ngx_http_scgi_reinit_request;
    u->process_header = ngx_http_scgi_process_status_line;
    u->abort_request = ngx_http_scgi_abort_request;
    u->finalize_request = ngx_http_scgi_finalize_request;
    r->state = 0;

    u->buffering = scf->upstream.buffering;

    u->pipe = ngx_pcalloc(r->pool, sizeof(ngx_event_pipe_t));
    if (u->pipe == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    u->pipe->input_filter = ngx_event_pipe_copy_input_filter;
    u->pipe->input_ctx = r;

    if (!scf->upstream.request_buffering
        && scf->upstream.pass_request_body
        && !r->headers_in.chunked)
    {
        r->request_body_no_buffering = 1;
    }

    rc = ngx_http_read_client_request_body(r, ngx_http_upstream_init);

    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    return NGX_DONE;
}
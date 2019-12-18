#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int ngx_uint_t ;
struct TYPE_30__ {int msec; int usec; int /*<<< orphan*/  sec; } ;
typedef  TYPE_5__ ngx_time_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  void* ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_28__ {int /*<<< orphan*/  trailers; int /*<<< orphan*/  headers; } ;
struct TYPE_31__ {scalar_t__ subrequests; int subrequest_in_memory; int waited; int background; int filter_need_in_memory; int internal; int expect_tested; int start_msec; int start_usec; int realloc_captures; int /*<<< orphan*/  captures_data; int /*<<< orphan*/  captures; int /*<<< orphan*/  ncaptures; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  phase_handler; int /*<<< orphan*/  content_handler; int /*<<< orphan*/  valid_unparsed_uri; int /*<<< orphan*/  valid_location; int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  method_name; int /*<<< orphan*/  method; TYPE_2__* main; int /*<<< orphan*/  start_sec; scalar_t__ uri_changes; int /*<<< orphan*/  main_filter_need_in_memory; int /*<<< orphan*/  discard_body; TYPE_7__* postponed; int /*<<< orphan*/  pool; int /*<<< orphan*/  log_handler; int /*<<< orphan*/  variables; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/ * post_subrequest; struct TYPE_31__* parent; int /*<<< orphan*/  schema; int /*<<< orphan*/  http_protocol; int /*<<< orphan*/  unparsed_uri; int /*<<< orphan*/  raw_uri; void* args; void* uri; int /*<<< orphan*/  request_line; int /*<<< orphan*/  http_version; int /*<<< orphan*/  stream; int /*<<< orphan*/  request_body; int /*<<< orphan*/  headers_in; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; TYPE_3__ headers_out; int /*<<< orphan*/ * ctx; TYPE_10__* connection; int /*<<< orphan*/  signature; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_32__ {struct TYPE_32__* next; int /*<<< orphan*/ * out; TYPE_6__* request; } ;
typedef  TYPE_7__ ngx_http_postponed_request_t ;
typedef  int /*<<< orphan*/  ngx_http_post_subrequest_t ;
struct TYPE_33__ {TYPE_4__* ctx; } ;
typedef  TYPE_8__ ngx_http_core_srv_conf_t ;
struct TYPE_34__ {scalar_t__ request_time_cache; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_25__ {TYPE_6__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_connection_t ;
struct TYPE_29__ {int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
struct TYPE_27__ {int count; } ;
struct TYPE_26__ {int usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_MAX_URI_CHANGES ; 
 int /*<<< orphan*/  NGX_HTTP_MODULE ; 
 int NGX_HTTP_SUBREQUEST_BACKGROUND ; 
 int NGX_HTTP_SUBREQUEST_CLONE ; 
 int NGX_HTTP_SUBREQUEST_IN_MEMORY ; 
 int NGX_HTTP_SUBREQUEST_WAITED ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  ngx_http_clear_accept_ranges (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_clear_last_modified (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_core_get_method ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_core_run_phases ; 
 TYPE_9__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_handler ; 
 int ngx_http_max_module ; 
 int /*<<< orphan*/  ngx_http_post_request (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_request_empty_handler ; 
 int /*<<< orphan*/  ngx_http_set_exten (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_update_location_config (TYPE_6__*) ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**,void**) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**) ; 
 TYPE_7__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* ngx_timeofday () ; 

ngx_int_t
ngx_http_subrequest(ngx_http_request_t *r,
    ngx_str_t *uri, ngx_str_t *args, ngx_http_request_t **psr,
    ngx_http_post_subrequest_t *ps, ngx_uint_t flags)
{
    ngx_time_t                    *tp;
    ngx_connection_t              *c;
    ngx_http_request_t            *sr;
    ngx_http_core_srv_conf_t      *cscf;
#if (T_NGX_RET_CACHE)
    ngx_http_core_loc_conf_t      *clcf;
    struct timeval                 tv;
#endif
    ngx_http_postponed_request_t  *pr, *p;

    if (r->subrequests == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "subrequests cycle while processing \"%V\"", uri);
        return NGX_ERROR;
    }

    /*
     * 1000 is reserved for other purposes.
     */
    if (r->main->count >= 65535 - 1000) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                      "request reference counter overflow "
                      "while processing \"%V\"", uri);
        return NGX_ERROR;
    }

    if (r->subrequest_in_memory) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "nested in-memory subrequest \"%V\"", uri);
        return NGX_ERROR;
    }

    sr = ngx_pcalloc(r->pool, sizeof(ngx_http_request_t));
    if (sr == NULL) {
        return NGX_ERROR;
    }

    sr->signature = NGX_HTTP_MODULE;

    c = r->connection;
    sr->connection = c;

    sr->ctx = ngx_pcalloc(r->pool, sizeof(void *) * ngx_http_max_module);
    if (sr->ctx == NULL) {
        return NGX_ERROR;
    }

    if (ngx_list_init(&sr->headers_out.headers, r->pool, 20,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    if (ngx_list_init(&sr->headers_out.trailers, r->pool, 4,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);
    sr->main_conf = cscf->ctx->main_conf;
    sr->srv_conf = cscf->ctx->srv_conf;
    sr->loc_conf = cscf->ctx->loc_conf;

    sr->pool = r->pool;

    sr->headers_in = r->headers_in;

    ngx_http_clear_content_length(sr);
    ngx_http_clear_accept_ranges(sr);
    ngx_http_clear_last_modified(sr);

    sr->request_body = r->request_body;

#if (NGX_HTTP_V2)
    sr->stream = r->stream;
#endif

    sr->method = NGX_HTTP_GET;
    sr->http_version = r->http_version;

    sr->request_line = r->request_line;
    sr->uri = *uri;

    if (args) {
        sr->args = *args;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "http subrequest \"%V?%V\"", uri, &sr->args);

    sr->subrequest_in_memory = (flags & NGX_HTTP_SUBREQUEST_IN_MEMORY) != 0;
    sr->waited = (flags & NGX_HTTP_SUBREQUEST_WAITED) != 0;
    sr->background = (flags & NGX_HTTP_SUBREQUEST_BACKGROUND) != 0;

#if (T_NGX_VARS)
    sr->raw_uri = r->raw_uri;
#endif
    sr->unparsed_uri = r->unparsed_uri;
    sr->method_name = ngx_http_core_get_method;
    sr->http_protocol = r->http_protocol;
    sr->schema = r->schema;

    ngx_http_set_exten(sr);

    sr->main = r->main;
    sr->parent = r;
    sr->post_subrequest = ps;
    sr->read_event_handler = ngx_http_request_empty_handler;
    sr->write_event_handler = ngx_http_handler;

    sr->variables = r->variables;

    sr->log_handler = r->log_handler;

    if (sr->subrequest_in_memory) {
        sr->filter_need_in_memory = 1;
    }

    if (!sr->background) {
        if (c->data == r && r->postponed == NULL) {
            c->data = sr;
        }

        pr = ngx_palloc(r->pool, sizeof(ngx_http_postponed_request_t));
        if (pr == NULL) {
            return NGX_ERROR;
        }

        pr->request = sr;
        pr->out = NULL;
        pr->next = NULL;

        if (r->postponed) {
            for (p = r->postponed; p->next; p = p->next) { /* void */ }
            p->next = pr;

        } else {
            r->postponed = pr;
        }
    }

    sr->internal = 1;

    sr->discard_body = r->discard_body;
    sr->expect_tested = 1;
    sr->main_filter_need_in_memory = r->main_filter_need_in_memory;

    sr->uri_changes = NGX_HTTP_MAX_URI_CHANGES + 1;
    sr->subrequests = r->subrequests - 1;

#if (T_NGX_RET_CACHE)
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (clcf->request_time_cache) {
        tp = ngx_timeofday();
        sr->start_sec = tp->sec;
        sr->start_msec = tp->msec;
#if (T_NGX_VARS)
        sr->start_usec = tp->usec;
#endif

    } else {
        ngx_gettimeofday(&tv);
        sr->start_sec = tv.tv_sec;
        sr->start_msec = tv.tv_usec / 1000;
        sr->start_usec = tv.tv_usec % 1000;
#if (T_NGX_VARS)
        sr->start_usec = tv.tv_usec % 1000;
#endif
    }

#else
    tp = ngx_timeofday();
    sr->start_sec = tp->sec;
    sr->start_msec = tp->msec;
#if (T_NGX_VARS)
    sr->start_usec = tp.usec;
#endif
#endif

    r->main->count++;

    *psr = sr;

    if (flags & NGX_HTTP_SUBREQUEST_CLONE) {
        sr->method = r->method;
        sr->method_name = r->method_name;
        sr->loc_conf = r->loc_conf;
        sr->valid_location = r->valid_location;
        sr->valid_unparsed_uri = r->valid_unparsed_uri;
        sr->content_handler = r->content_handler;
        sr->phase_handler = r->phase_handler;
        sr->write_event_handler = ngx_http_core_run_phases;

#if (NGX_PCRE)
        sr->ncaptures = r->ncaptures;
        sr->captures = r->captures;
        sr->captures_data = r->captures_data;
        sr->realloc_captures = 1;
        r->realloc_captures = 1;
#endif

        ngx_http_update_location_config(sr);
    }

    return ngx_http_post_request(sr, NULL);
}
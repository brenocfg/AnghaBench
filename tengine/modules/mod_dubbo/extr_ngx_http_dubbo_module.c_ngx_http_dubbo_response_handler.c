#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_22__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_26__ {TYPE_18__ value; TYPE_17__ key; } ;
typedef  TYPE_3__ ngx_keyval_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {size_t status_n; int content_length_n; } ;
struct TYPE_27__ {TYPE_2__* state; TYPE_1__ headers_in; TYPE_7__* out_bufs; int /*<<< orphan*/  free_bufs; } ;
typedef  TYPE_4__ ngx_http_upstream_t ;
struct TYPE_28__ {int /*<<< orphan*/  pool; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_29__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_30__ {TYPE_8__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_31__ {int flush; int memory; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_32__ {size_t nelts; TYPE_3__* elts; } ;
typedef  TYPE_9__ ngx_array_t ;
struct TYPE_25__ {size_t status; } ;
struct TYPE_21__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 void* NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 size_t ngx_atoi (int /*<<< orphan*/ *,int) ; 
 TYPE_7__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_dubbo_add_response_header (TYPE_5__*,TYPE_17__*,TYPE_18__*) ; 
 TYPE_12__ ngx_http_dubbo_str_body ; 
 TYPE_11__ ngx_http_dubbo_str_status ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_dubbo_response_handler(ngx_connection_t *pc, ngx_http_request_t *r, ngx_array_t *result)
{
    ngx_http_upstream_t             *u;
    ngx_keyval_t                    *kv;
    ngx_uint_t                       i;
    ngx_chain_t                     *cl;
    ngx_buf_t                       *buf;
    ngx_uint_t                       status;

    u = r->upstream;

    if (u->out_bufs != NULL) {
        ngx_log_error(NGX_LOG_ERR, pc->log, 0, "dubbo [%V]: out_bufs is not NULL, %p", r);
        return NGX_ERROR;
    }

    u->headers_in.status_n = NGX_HTTP_BAD_GATEWAY;
    u->state->status = NGX_HTTP_BAD_GATEWAY;

    kv = result->elts;
    for (i=0; i < result->nelts; i++) {
        if (kv[i].key.len == 4 && 0 == ngx_strncasecmp(kv[i].key.data,
                    ngx_http_dubbo_str_body.data, ngx_http_dubbo_str_body.len)) {
            if (kv[i].value.len > 0 && kv[i].value.data != NULL) {
                cl = ngx_chain_get_free_buf(r->pool, &u->free_bufs);
                if (cl == NULL) {
                    return NGX_ERROR;
                }

                u->out_bufs = cl;
                buf = u->out_bufs->buf;

                buf->flush = 1;
                buf->memory = 1;

                buf->pos = kv[i].value.data;
                buf->last = kv[i].value.data + kv[i].value.len;
            }

            u->headers_in.content_length_n = kv[i].value.len;
        } else if (kv[i].key.len == 6 && 0 == ngx_strncasecmp(kv[i].key.data, ngx_http_dubbo_str_status.data, ngx_http_dubbo_str_status.len)) {
            status = ngx_atoi(kv[i].value.data, kv[i].value.len);
            u->headers_in.status_n = status;
            u->state->status = status;
        } else {
            if (NGX_OK != ngx_http_dubbo_add_response_header(r, &kv[i].key, &kv[i].value)) {
                return NGX_ERROR;
            }
        }
    }

    return NGX_OK;
}
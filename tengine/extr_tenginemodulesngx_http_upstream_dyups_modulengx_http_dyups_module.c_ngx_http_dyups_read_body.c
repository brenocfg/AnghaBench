#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  pool; TYPE_2__* request_body; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_14__ {TYPE_3__* next; TYPE_6__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_15__ {size_t last; size_t pos; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_12__ {TYPE_6__* buf; } ;
struct TYPE_11__ {TYPE_5__* bufs; } ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 void* ngx_cpymem (size_t,size_t,size_t) ; 
 TYPE_6__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_dyups_read_body(ngx_http_request_t *r)
{
    size_t        len;
    ngx_buf_t    *buf, *next, *body;
    ngx_chain_t  *cl;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "[dyups] interface read post body");

    cl = r->request_body->bufs;
    buf = cl->buf;

    if (cl->next == NULL) {

        return buf;

    } else {

        next = cl->next->buf;
        len = (buf->last - buf->pos) + (next->last - next->pos);

        body = ngx_create_temp_buf(r->pool, len);
        if (body == NULL) {
            return NULL;
        }

        body->last = ngx_cpymem(body->last, buf->pos, buf->last - buf->pos);
        body->last = ngx_cpymem(body->last, next->pos, next->last - next->pos);
    }

    return body;
}
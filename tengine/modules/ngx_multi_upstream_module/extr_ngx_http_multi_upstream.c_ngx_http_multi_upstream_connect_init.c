#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_queue_t ;
struct TYPE_25__ {TYPE_8__* data; } ;
typedef  TYPE_5__ ngx_multi_data_t ;
struct TYPE_26__ {int connected; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ ngx_multi_connection_t ;
struct TYPE_24__ {scalar_t__ limit; TYPE_9__* connection; int /*<<< orphan*/ * out; int /*<<< orphan*/ ** last; } ;
struct TYPE_23__ {int /*<<< orphan*/  sendfile; TYPE_8__* filter_ctx; } ;
struct TYPE_27__ {TYPE_4__ writer; TYPE_3__ output; int /*<<< orphan*/  read_event_handler; int /*<<< orphan*/  write_event_handler; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
struct TYPE_28__ {TYPE_7__* upstream; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_29__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  sendfile; TYPE_2__* write; TYPE_1__* read; TYPE_8__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_connection_t ;
struct TYPE_20__ {size_t nelts; TYPE_5__* elts; } ;
typedef  TYPE_10__ ngx_array_t ;
struct TYPE_22__ {void* handler; } ;
struct TYPE_21__ {void* handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_10__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (TYPE_10__*) ; 
 TYPE_6__* ngx_get_multi_connection (TYPE_9__*) ; 
 void* ngx_http_multi_upstream_handler ; 
 int /*<<< orphan*/  ngx_http_multi_upstream_init_request (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_process_header ; 
 int /*<<< orphan*/  ngx_http_upstream_send_request_handler ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/ * ngx_queue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_queue_sentinel (int /*<<< orphan*/ *) ; 

void
ngx_http_multi_upstream_connect_init(ngx_connection_t *pc)
{
    ngx_multi_connection_t              *multi_c;
    ngx_http_request_t                  *fake_r, *r;
    ngx_http_upstream_t                 *fake_u;
    ngx_queue_t                         *data, *q;
    ngx_array_t                          tmp;
    ngx_multi_data_t                    *item;
    size_t                               i;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                   "multi: http upstream init connection: %p", pc);

    fake_r = pc->data;
    fake_u = fake_r->upstream;

    pc->read->handler = ngx_http_multi_upstream_handler;
    pc->write->handler = ngx_http_multi_upstream_handler;

    fake_u->write_event_handler = ngx_http_upstream_send_request_handler;
    fake_u->read_event_handler = ngx_http_upstream_process_header;
    fake_u->output.filter_ctx = fake_r;
    fake_u->output.sendfile = pc->sendfile;

    fake_u->writer.out = NULL;
    fake_u->writer.last = &fake_u->writer.out;
    fake_u->writer.connection = pc;
    fake_u->writer.limit = 0;


    //init
    multi_c = ngx_get_multi_connection(pc);
    multi_c->connected = 1;
    data = &multi_c->data;

    if (NGX_OK != ngx_array_init(&tmp, pc->pool, 4, sizeof(ngx_multi_data_t))) {
        return;
    }

    for (q = ngx_queue_head(data);
            q != ngx_queue_sentinel(data);
            q = ngx_queue_next(q))
    {
        item = ngx_array_push(&tmp);
        if (item == NULL) {
            return;
        }
        *item = *(ngx_multi_data_t*) q;
    }

    item = tmp.elts;
    for (i=0; i < tmp.nelts; i++) {

        r = item[i].data;

        ngx_http_multi_upstream_init_request(pc, r);
    }
}
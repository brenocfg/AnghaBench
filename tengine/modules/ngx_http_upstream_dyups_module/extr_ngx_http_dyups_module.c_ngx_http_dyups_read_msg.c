#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ ngx_slab_pool_t ;
struct TYPE_12__ {scalar_t__ deleted; int /*<<< orphan*/  dynamic; } ;
typedef  TYPE_3__ ngx_http_dyups_srv_conf_t ;
struct TYPE_10__ {size_t nelts; TYPE_3__* elts; } ;
struct TYPE_13__ {int read_msg_log; int /*<<< orphan*/  read_msg_timeout; TYPE_1__ dy_upstreams; } ;
typedef  TYPE_4__ ngx_http_dyups_main_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; TYPE_4__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_15__ {TYPE_2__* shpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_dyups_add_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_8__ ngx_dyups_global_ctx ; 
 int /*<<< orphan*/  ngx_http_dyups_read_msg_locked (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_dyups_read_msg(ngx_event_t *ev)
{
    ngx_uint_t                   i, count, s_count, d_count;
    ngx_slab_pool_t             *shpool;
    ngx_http_dyups_srv_conf_t   *duscfs, *duscf;
    ngx_http_dyups_main_conf_t  *dmcf;

    dmcf = ev->data;
    shpool = ngx_dyups_global_ctx.shpool;

    count = 0;
    s_count = 0;
    d_count = 0;

    duscfs = dmcf->dy_upstreams.elts;
    for (i = 0; i < dmcf->dy_upstreams.nelts; i++) {

        duscf = &duscfs[i];

        if (!duscf->dynamic) {
            s_count++;
            continue;
        }

        if (duscf->deleted) {
            d_count++;
            continue;
        }

        count++;
    }

    if (dmcf->read_msg_log == 1) {
        ngx_log_error(NGX_LOG_INFO, ev->log, 0,
                      "[dyups] has %ui upstreams, %ui static, %ui deleted, all %ui",
                      count, s_count, d_count, dmcf->dy_upstreams.nelts);
    }

    ngx_shmtx_lock(&shpool->mutex);

    ngx_http_dyups_read_msg_locked(ev);

    ngx_shmtx_unlock(&shpool->mutex);

    ngx_dyups_add_timer(ev, dmcf->read_msg_timeout);
}
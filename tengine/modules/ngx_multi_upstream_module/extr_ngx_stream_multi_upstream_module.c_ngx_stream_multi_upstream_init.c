#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  init; } ;
struct TYPE_12__ {TYPE_1__ peer; } ;
typedef  TYPE_2__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_13__ {scalar_t__ (* original_init_upstream ) (TYPE_4__*,TYPE_2__*) ;int /*<<< orphan*/  cache; int /*<<< orphan*/  original_init_peer; } ;
typedef  TYPE_3__ ngx_stream_multi_upstream_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_stream_conf_upstream_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_multi_upstream_init_peer ; 
 int /*<<< orphan*/  ngx_stream_multi_upstream_module ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_multi_upstream_init(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{
    ngx_stream_multi_upstream_srv_conf_t  *kcf;

    ngx_log_debug0(NGX_LOG_DEBUG_STREAM, cf->log, 0,
                   "multi: init multi stream");

    kcf = ngx_stream_conf_upstream_srv_conf(us,
                                          ngx_stream_multi_upstream_module);

    if (kcf->original_init_upstream(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    kcf->original_init_peer = us->peer.init;

    us->peer.init = ngx_stream_multi_upstream_init_peer;

    ngx_queue_init(&kcf->cache);

    return NGX_OK;
}
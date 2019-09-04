#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_sysguard_rt_ring_t ;
typedef  int /*<<< orphan*/  ngx_http_sysguard_rt_node_t ;
struct TYPE_8__ {scalar_t__ enable; scalar_t__ load; scalar_t__ cpuusage; scalar_t__ swap; scalar_t__ rt; scalar_t__ rt_period; scalar_t__ interval; scalar_t__ cpu_interval; TYPE_2__* rt_ring; int /*<<< orphan*/  mode; int /*<<< orphan*/  log_level; int /*<<< orphan*/  free; int /*<<< orphan*/  rt_action; int /*<<< orphan*/  free_action; int /*<<< orphan*/  swap_action; int /*<<< orphan*/  cpuusage_action; int /*<<< orphan*/  load_action; } ;
typedef  TYPE_3__ ngx_http_sysguard_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_7__ {int nr_slots; TYPE_1__* slots; scalar_t__ current; } ;
struct TYPE_6__ {int /*<<< orphan*/  stamp; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 int /*<<< orphan*/  NGX_CONF_UNSET_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_SYSGUARD_MODE_OR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_time () ; 

__attribute__((used)) static char *
ngx_http_sysguard_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_sysguard_conf_t  *prev = parent;
    ngx_http_sysguard_conf_t  *conf = child;

    ngx_conf_merge_value(conf->enable, prev->enable, 0);
    ngx_conf_merge_str_value(conf->load_action, prev->load_action, "");
    ngx_conf_merge_str_value(conf->cpuusage_action, prev->cpuusage_action, "");
    ngx_conf_merge_str_value(conf->swap_action, prev->swap_action, "");
    ngx_conf_merge_str_value(conf->free_action, prev->free_action, "");
    ngx_conf_merge_str_value(conf->rt_action, prev->rt_action, "");
    ngx_conf_merge_value(conf->load, prev->load, NGX_CONF_UNSET);
    ngx_conf_merge_value(conf->cpuusage, prev->cpuusage, NGX_CONF_UNSET);
    ngx_conf_merge_value(conf->swap, prev->swap, NGX_CONF_UNSET);
    ngx_conf_merge_size_value(conf->free, prev->free, NGX_CONF_UNSET_SIZE);
    ngx_conf_merge_value(conf->rt, prev->rt, NGX_CONF_UNSET);
    ngx_conf_merge_value(conf->rt_period, prev->rt_period, 1);
    ngx_conf_merge_value(conf->interval, prev->interval, 1);
    ngx_conf_merge_value(conf->cpu_interval, prev->cpu_interval, 3);
    ngx_conf_merge_uint_value(conf->log_level, prev->log_level, NGX_LOG_ERR);
    ngx_conf_merge_uint_value(conf->mode, prev->mode,
                              NGX_HTTP_SYSGUARD_MODE_OR);


    if (conf->rt != NGX_CONF_UNSET) {
        /* init glcf->ring */
        conf->rt_ring = ngx_pcalloc(cf->pool,
                                    sizeof(ngx_http_sysguard_rt_ring_t));
        if (conf->rt_ring == NULL) {
            return NGX_CONF_ERROR;
        }

        conf->rt_ring->slots = ngx_pcalloc(cf->pool,
                         sizeof(ngx_http_sysguard_rt_node_t) * conf->rt_period);
        if (conf->rt_ring->slots == NULL) {
            return NGX_CONF_ERROR;
        }

        conf->rt_ring->nr_slots = conf->rt_period;
        conf->rt_ring->current = 0;
        conf->rt_ring->slots[0].stamp = ngx_time();
    }

    return NGX_CONF_OK;
}
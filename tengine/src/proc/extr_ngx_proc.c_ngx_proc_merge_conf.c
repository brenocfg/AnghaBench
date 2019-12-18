#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  respawn; int /*<<< orphan*/  count; int /*<<< orphan*/  delay_start; } ;
typedef  TYPE_1__ ngx_proc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_proc_merge_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_proc_conf_t  *prev = parent;
    ngx_proc_conf_t  *conf = child;

    ngx_conf_merge_msec_value(conf->delay_start, prev->delay_start, 300);
    ngx_conf_merge_uint_value(conf->count, prev->count, 1);
    ngx_conf_merge_value(conf->respawn, prev->respawn, 1);

    return NGX_CONF_OK;
}
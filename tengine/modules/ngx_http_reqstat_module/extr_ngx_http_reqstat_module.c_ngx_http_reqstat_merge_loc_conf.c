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
struct TYPE_2__ {int /*<<< orphan*/  user_defined_str; int /*<<< orphan*/  user_select; int /*<<< orphan*/  display; int /*<<< orphan*/  monitor; int /*<<< orphan*/  bypass; int /*<<< orphan*/  lazy; } ;
typedef  TYPE_1__ ngx_http_reqstat_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_reqstat_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child)
{
    ngx_http_reqstat_conf_t      *conf = child;
    ngx_http_reqstat_conf_t      *prev = parent;

    ngx_conf_merge_value(conf->lazy, prev->lazy, 0);
    ngx_conf_merge_ptr_value(conf->bypass, prev->bypass, NULL);
    ngx_conf_merge_ptr_value(conf->monitor, prev->monitor, NULL);
    ngx_conf_merge_ptr_value(conf->display, prev->display, NULL);
    ngx_conf_merge_ptr_value(conf->user_select, prev->user_select, NULL);
    ngx_conf_merge_ptr_value(conf->user_defined_str, prev->user_defined_str, NULL);

    return NGX_CONF_OK;
}
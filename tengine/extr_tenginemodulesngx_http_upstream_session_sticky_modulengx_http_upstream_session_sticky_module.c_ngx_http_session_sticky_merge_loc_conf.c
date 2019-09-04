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
struct TYPE_2__ {int /*<<< orphan*/  uscf; } ;
typedef  TYPE_1__ ngx_http_ss_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_session_sticky_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child)
{
    ngx_http_ss_loc_conf_t  *prev = parent;
    ngx_http_ss_loc_conf_t  *conf = child;

    ngx_conf_merge_ptr_value(conf->uscf, prev->uscf, NGX_CONF_UNSET_PTR);

    return NGX_CONF_OK;
}
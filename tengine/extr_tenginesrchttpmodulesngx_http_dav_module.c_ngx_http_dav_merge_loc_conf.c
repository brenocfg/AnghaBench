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
struct TYPE_2__ {int /*<<< orphan*/  create_full_put_path; int /*<<< orphan*/  access; int /*<<< orphan*/  min_delete_depth; int /*<<< orphan*/  methods; } ;
typedef  TYPE_1__ ngx_http_dav_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int NGX_CONF_BITMASK_SET ; 
 char* NGX_CONF_OK ; 
 int NGX_HTTP_DAV_OFF ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_dav_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_dav_loc_conf_t  *prev = parent;
    ngx_http_dav_loc_conf_t  *conf = child;

    ngx_conf_merge_bitmask_value(conf->methods, prev->methods,
                         (NGX_CONF_BITMASK_SET|NGX_HTTP_DAV_OFF));

    ngx_conf_merge_uint_value(conf->min_delete_depth,
                         prev->min_delete_depth, 0);

    ngx_conf_merge_uint_value(conf->access, prev->access, 0600);

    ngx_conf_merge_value(conf->create_full_put_path,
                         prev->create_full_put_path, 0);

    return NGX_CONF_OK;
}
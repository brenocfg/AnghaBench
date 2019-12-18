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
struct TYPE_2__ {scalar_t__ push_preload; int /*<<< orphan*/ * pushes; scalar_t__ push; int /*<<< orphan*/  chunk_size; } ;
typedef  TYPE_1__ ngx_http_v2_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static char *
ngx_http_v2_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_v2_loc_conf_t *prev = parent;
    ngx_http_v2_loc_conf_t *conf = child;

    ngx_conf_merge_size_value(conf->chunk_size, prev->chunk_size, 8 * 1024);

    ngx_conf_merge_value(conf->push, prev->push, 1);

    if (conf->push && conf->pushes == NULL) {
        conf->pushes = prev->pushes;
    }

    ngx_conf_merge_value(conf->push_preload, prev->push_preload, 0);

    return NGX_CONF_OK;
}
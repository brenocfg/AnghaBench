#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ngx_http_upstream_srv_conf_t ;
struct TYPE_6__ {int /*<<< orphan*/  rbtree; } ;
typedef  TYPE_2__ ngx_http_upstream_main_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rbtree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_del_upstream_filter(ngx_http_upstream_main_conf_t *umcf,
    ngx_http_upstream_srv_conf_t *uscf)
{
#if (NGX_HTTP_UPSTREAM_RBTREE)
    ngx_rbtree_delete(&umcf->rbtree, &uscf->node);
#endif
    return NGX_OK;
}
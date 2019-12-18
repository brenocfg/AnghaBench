#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_4__ node; TYPE_1__ host; } ;
typedef  TYPE_2__ ngx_http_upstream_srv_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  rbtree; } ;
typedef  TYPE_3__ ngx_http_upstream_main_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_crc32_short (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_add_upstream_filter(ngx_http_upstream_main_conf_t *umcf,
    ngx_http_upstream_srv_conf_t *uscf)
{
#if (NGX_HTTP_UPSTREAM_RBTREE)
    uscf->node.key = ngx_crc32_short(uscf->host.data, uscf->host.len);
    ngx_rbtree_insert(&umcf->rbtree, &uscf->node);
#endif

    return NGX_OK;
}
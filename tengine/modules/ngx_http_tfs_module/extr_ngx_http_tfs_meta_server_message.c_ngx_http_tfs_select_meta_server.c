#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int /*<<< orphan*/  user_id; int /*<<< orphan*/  app_id; } ;
struct TYPE_10__ {TYPE_2__* loc_conf; TYPE_3__ r_ctx; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_11__ {void* user_id; void* app_id; } ;
typedef  TYPE_5__ ngx_http_tfs_meta_hh_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_7__ {int /*<<< orphan*/ * table; } ;
struct TYPE_8__ {TYPE_1__ meta_server_table; } ;

/* Variables and functions */
 size_t NGX_HTTP_TFS_METASERVER_COUNT ; 
 void* ngx_hton64 (int /*<<< orphan*/ ) ; 
 size_t ngx_http_tfs_murmur_hash (int /*<<< orphan*/ *,int) ; 

ngx_http_tfs_inet_t *
ngx_http_tfs_select_meta_server(ngx_http_tfs_t *t)
{
    uint32_t                hash, index;
    ngx_http_tfs_meta_hh_t  h;

    h.app_id = ngx_hton64(t->r_ctx.app_id);
    h.user_id = ngx_hton64(t->r_ctx.user_id);

    hash = ngx_http_tfs_murmur_hash((u_char *) &h,
                                    sizeof(ngx_http_tfs_meta_hh_t));

    index = hash % NGX_HTTP_TFS_METASERVER_COUNT;

    return &(t->loc_conf->meta_server_table.table[index]);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {TYPE_9__* server; } ;
typedef  TYPE_1__ ngx_http_tfs_tair_server_addr_info_t ;
struct TYPE_18__ {TYPE_3__* rc_info_node; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_25__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {size_t logical_cluster_count; size_t unlink_cluster_group_count; TYPE_8__* unlink_cluster_groups; TYPE_9__ remote_block_cache_info; scalar_t__ need_duplicate; TYPE_6__* logical_clusters; scalar_t__ rc_servers_count; int /*<<< orphan*/ * rc_servers; } ;
typedef  TYPE_3__ ngx_http_tfs_rcs_info_t ;
struct TYPE_20__ {int /*<<< orphan*/  shpool; } ;
typedef  TYPE_4__ ngx_http_tfs_rc_ctx_t ;
struct TYPE_21__ {TYPE_9__ ns_vip_text; scalar_t__ cluster_id; TYPE_9__ cluster_id_text; } ;
typedef  TYPE_5__ ngx_http_tfs_physical_cluster_t ;
struct TYPE_22__ {int dup_server_addr_hash; size_t rw_cluster_count; TYPE_5__* rw_clusters; scalar_t__ need_duplicate; TYPE_1__ dup_server_info; } ;
typedef  TYPE_6__ ngx_http_tfs_logical_cluster_t ;
struct TYPE_23__ {TYPE_9__ ns_vip_text; } ;
typedef  TYPE_7__ ngx_http_tfs_group_info_t ;
struct TYPE_24__ {size_t info_count; TYPE_7__* group_info; } ;
typedef  TYPE_8__ ngx_http_tfs_cluster_group_info_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_TFS_TAIR_SERVER_ADDR_PART_COUNT ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_tfs_parse_rc_info (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_update_rc_servers (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_slab_free_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_9__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_update_info_node(ngx_http_tfs_t *t, ngx_http_tfs_rc_ctx_t *rc_ctx,
    ngx_http_tfs_rcs_info_t *rc_info_node, u_char *base_info)
{
    u_char                                *p;
    ngx_int_t                              rc;
    ngx_uint_t                             i, j;
    ngx_http_tfs_group_info_t             *group_info;
    ngx_http_tfs_logical_cluster_t        *logical_cluster;
    ngx_http_tfs_physical_cluster_t       *physical_cluster;
    ngx_http_tfs_cluster_group_info_t     *cluster_group_info;
    ngx_http_tfs_tair_server_addr_info_t  *dup_server_info;

    p = base_info;

    /* free old rc servers */
    if (rc_info_node->rc_servers != NULL) {
        ngx_slab_free_locked(rc_ctx->shpool, rc_info_node->rc_servers);
    }
    rc_info_node->rc_servers_count = 0;

    /* free old cluster data */
    logical_cluster = rc_info_node->logical_clusters;
    for (i = 0; i < rc_info_node->logical_cluster_count; i++) {
        /* free old duplicate server info */
        if (logical_cluster->need_duplicate) {
            dup_server_info = &logical_cluster->dup_server_info;

            for (j = 0; j < NGX_HTTP_TFS_TAIR_SERVER_ADDR_PART_COUNT; j++) {
                if (dup_server_info->server[j].data == NULL) {
                    break;
                }
                ngx_slab_free_locked(rc_ctx->shpool,
                                     dup_server_info->server[j].data);
                ngx_str_null(&dup_server_info->server[j]);
            }
            logical_cluster->dup_server_addr_hash = -1;
            logical_cluster->need_duplicate = 0;
        }

        physical_cluster = logical_cluster->rw_clusters;
        for (j = 0; j < logical_cluster->rw_cluster_count; i++) {
            if (physical_cluster->cluster_id_text.len <= 0
                || physical_cluster->cluster_id_text.data == NULL)
            {
                break;
            }
            ngx_slab_free_locked(rc_ctx->shpool,
                                 physical_cluster->cluster_id_text.data);
            ngx_str_null(&physical_cluster->cluster_id_text);
            physical_cluster->cluster_id = 0;

            if (physical_cluster->ns_vip_text.len <= 0
                || physical_cluster->ns_vip_text.data == NULL)
            {
                break;
            }
            ngx_slab_free_locked(rc_ctx->shpool,
                                 physical_cluster->ns_vip_text.data);
            ngx_str_null(&physical_cluster->ns_vip_text);

            physical_cluster++;
        }
        logical_cluster->rw_cluster_count = 0;

        logical_cluster++;
    }
    rc_info_node->logical_cluster_count = 0;

    /* reset need duplicate flag */
    rc_info_node->need_duplicate = 0;

    /* free old remote block cache info */
    if (rc_info_node->remote_block_cache_info.len > 0
        && rc_info_node->remote_block_cache_info.data != NULL)
    {
        ngx_slab_free_locked(rc_ctx->shpool,
                             rc_info_node->remote_block_cache_info.data);
        ngx_str_null(&rc_info_node->remote_block_cache_info);
    }
    rc_info_node->remote_block_cache_info.len = 0;

    /* free old unlink cluster */
    cluster_group_info = rc_info_node->unlink_cluster_groups;
    for (i = 0; i < rc_info_node->unlink_cluster_group_count; i++) {
        for (j = 0; j < cluster_group_info[i].info_count; j++) {
            group_info = &cluster_group_info[i].group_info[j];
            if (group_info->ns_vip_text.len <= 0
                || group_info->ns_vip_text.data == NULL)
            {
                break;
            }
            ngx_slab_free_locked(rc_ctx->shpool, group_info->ns_vip_text.data);
            ngx_str_null(&group_info->ns_vip_text);
        }
    }
    rc_info_node->unlink_cluster_group_count = 0;

    /* parse rc info */
    rc = ngx_http_tfs_parse_rc_info(rc_info_node, rc_ctx, p);
    if (rc == NGX_ERROR) {
        return NGX_ERROR;
    }

    t->rc_info_node = rc_info_node;
    ngx_http_tfs_update_rc_servers(t, rc_info_node);

    return NGX_OK;
}
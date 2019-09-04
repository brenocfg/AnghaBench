#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_tair_server_addr_info_t ;
struct TYPE_14__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int rc_servers_count; int logical_cluster_count; int need_duplicate; int report_interval; scalar_t__ unlink_cluster_group_count; int use_remote_block_cache; TYPE_8__* unlink_cluster_groups; TYPE_2__ remote_block_cache_info; void* meta_root_server; void* modify_time; TYPE_6__* logical_clusters; int /*<<< orphan*/ * rc_servers; } ;
typedef  TYPE_3__ ngx_http_tfs_rcs_info_t ;
struct TYPE_16__ {int /*<<< orphan*/  shpool; } ;
typedef  TYPE_4__ ngx_http_tfs_rc_ctx_t ;
struct TYPE_12__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int cluster_stat; int access_type; int /*<<< orphan*/  ns_vip; TYPE_11__ ns_vip_text; TYPE_1__ cluster_id_text; scalar_t__ cluster_id; } ;
typedef  TYPE_5__ ngx_http_tfs_physical_cluster_t ;
struct TYPE_18__ {int rw_cluster_count; TYPE_5__* rw_clusters; int /*<<< orphan*/  dup_server_addr_hash; int /*<<< orphan*/  dup_server_info; scalar_t__ need_duplicate; } ;
typedef  TYPE_6__ ngx_http_tfs_logical_cluster_t ;
struct TYPE_19__ {int group_seq; int /*<<< orphan*/  ns_vip; TYPE_11__ ns_vip_text; } ;
typedef  TYPE_7__ ngx_http_tfs_group_info_t ;
struct TYPE_20__ {int cluster_id; scalar_t__ info_count; TYPE_7__* group_info; scalar_t__ group_count; } ;
typedef  TYPE_8__ ngx_http_tfs_cluster_group_info_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  ngx_http_tfs_expire_and_alloc (int /*<<< orphan*/ *,int) ; 
 int ngx_http_tfs_get_cluster_id (scalar_t__*) ; 
 int /*<<< orphan*/  ngx_http_tfs_parse_inet (TYPE_11__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_tfs_parse_tair_server_addr_info (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  ngx_murmur_hash2 (scalar_t__*,scalar_t__) ; 
 void* ngx_slab_alloc_locked (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_rc_info(ngx_http_tfs_rcs_info_t *rc_info_node,
    ngx_http_tfs_rc_ctx_t *rc_ctx,  u_char *data)
{
    u_char                                *p;
    uint32_t                               cluster_id, cluster_id_len;
    uint32_t                               len, unlink_cluster_count;
    ngx_int_t                              dup_info_size, rc;
    ngx_uint_t                             i, j;
    ngx_http_tfs_group_info_t             *group_info;
    ngx_http_tfs_logical_cluster_t        *logical_cluster;
    ngx_http_tfs_physical_cluster_t       *physical_cluster;
    ngx_http_tfs_cluster_group_info_t     *cluster_group_info;
    ngx_http_tfs_tair_server_addr_info_t  *dup_server_info;

    p = data;

    /* rc servers count */
    rc_info_node->rc_servers_count = *((uint32_t *) p);
    p += sizeof(uint32_t);

    if (rc_info_node->rc_servers_count > 0) {
        rc_info_node->rc_servers =
            ngx_slab_alloc_locked(rc_ctx->shpool,
                                  rc_info_node->rc_servers_count
                                   * sizeof(uint64_t));
        if (rc_info_node->rc_servers == NULL) {
            ngx_http_tfs_expire_and_alloc(rc_info_node->rc_servers,
                                          rc_info_node->rc_servers_count
                                           * sizeof(uint64_t));
        }

        ngx_memcpy(rc_info_node->rc_servers, p,
                   rc_info_node->rc_servers_count * sizeof(uint64_t));
        p += sizeof(uint64_t) * rc_info_node->rc_servers_count;
    }

    /* logical cluster count */
    rc_info_node->logical_cluster_count = *((uint32_t *) p);
    p += sizeof(uint32_t);

    logical_cluster = rc_info_node->logical_clusters;
    for (i = 0; i < rc_info_node->logical_cluster_count; i++) {
        logical_cluster->need_duplicate = *p;
        p += sizeof(uint8_t);

        if (logical_cluster->need_duplicate) {
            len = *((uint32_t *) p);
            p += sizeof(uint32_t);

            if (len > 0) {
                dup_info_size = len - 1;
                dup_server_info = &logical_cluster->dup_server_info;

                rc = ngx_http_tfs_parse_tair_server_addr_info(dup_server_info,
                                                              p,
                                                              dup_info_size,
                                                              rc_ctx->shpool,
                                                              1);
                if (rc == NGX_ERROR) {
                    return NGX_ERROR;
                }

                logical_cluster->dup_server_addr_hash =
                    ngx_murmur_hash2(p, dup_info_size);
                p += dup_info_size + 1;

                rc_info_node->need_duplicate = 1;
            }
        }

        logical_cluster->rw_cluster_count = *((uint32_t *) p);
        p += sizeof(uint32_t);

        physical_cluster = logical_cluster->rw_clusters;
        for (j = 0; j < logical_cluster->rw_cluster_count; j++) {
            /* cluster stat */
            physical_cluster->cluster_stat = *((uint32_t *) p);
            p += sizeof(uint32_t);

            /* access type */
            physical_cluster->access_type = *((uint32_t *) p);
            p += sizeof(uint32_t);

            /* cluster id */
            len = *((uint32_t *) p);
            if (len <= 0) {
                physical_cluster->cluster_id_text.len = 0;
                return NGX_ERROR;
            }

            physical_cluster->cluster_id_text.len = len - 1;
            p += sizeof(uint32_t);

            physical_cluster->cluster_id_text.data =
                ngx_slab_alloc_locked(rc_ctx->shpool,
                                      physical_cluster->cluster_id_text.len);
            if (physical_cluster->cluster_id_text.data == NULL) {
                ngx_http_tfs_expire_and_alloc(
                                         physical_cluster->cluster_id_text.data,
                                         physical_cluster->cluster_id_text.len);
            }
            ngx_memcpy(physical_cluster->cluster_id_text.data, p,
                       physical_cluster->cluster_id_text.len);
            /* this cluster id need get from ns */
            physical_cluster->cluster_id = 0;
            p += physical_cluster->cluster_id_text.len + 1;

            /* name server vip */
            len = *((uint32_t *) p);
            if (len <= 0) {
                physical_cluster->ns_vip_text.len = 0;
                return NGX_ERROR;
            }

            physical_cluster->ns_vip_text.len = len - 1;
            p += sizeof(uint32_t);

            physical_cluster->ns_vip_text.data =
                ngx_slab_alloc_locked(rc_ctx->shpool,
                                      physical_cluster->ns_vip_text.len);
            if (physical_cluster->ns_vip_text.data == NULL) {
                ngx_http_tfs_expire_and_alloc(physical_cluster->ns_vip_text.data,
                                             physical_cluster->ns_vip_text.len);
            }
            ngx_memcpy(physical_cluster->ns_vip_text.data, p,
                       physical_cluster->ns_vip_text.len);

            p += physical_cluster->ns_vip_text.len + 1;

            ngx_http_tfs_parse_inet(&physical_cluster->ns_vip_text,
                                    &physical_cluster->ns_vip);

            physical_cluster++;
        }

        logical_cluster++;
    }

    /* report interval */
    rc_info_node->report_interval = *((uint32_t *) p);
    p += sizeof(uint32_t);

    /* modify time */
    rc_info_node->modify_time = *((uint64_t *) p);
    p += sizeof(uint64_t);

    /* root server */
    rc_info_node->meta_root_server = *((uint64_t *) p);
    p += sizeof(uint64_t);

    /* remote block cache */
    len = *((uint32_t *) p);
    p += sizeof(uint32_t);
    rc_info_node->remote_block_cache_info.len = 0;

    if (len > 0) {
        rc_info_node->remote_block_cache_info.len = len - 1;

        rc_info_node->remote_block_cache_info.data =
            ngx_slab_alloc_locked(rc_ctx->shpool,
                                  rc_info_node->remote_block_cache_info.len);
        if (rc_info_node->remote_block_cache_info.data == NULL) {
            ngx_http_tfs_expire_and_alloc(
                                     rc_info_node->remote_block_cache_info.data,
                                     rc_info_node->remote_block_cache_info.len);
        }

        ngx_memcpy(rc_info_node->remote_block_cache_info.data, p,
                   len - 1);
        p += len;
    }

    /* unlink & update cluster */
    /* this count is physical cluster count */
    unlink_cluster_count = *((uint32_t *) p);
    p += sizeof(uint32_t);

    rc_info_node->unlink_cluster_group_count = 0;

    for (i = 0; i < unlink_cluster_count; i++) {
        /* skip cluster_stat */
        p += sizeof(uint32_t);
        /* skip access type */
        p += sizeof(uint32_t);

        cluster_id_len = *((uint32_t *) p);
        p += sizeof(uint32_t);

        cluster_id = ngx_http_tfs_get_cluster_id(p);
        p += cluster_id_len;

        for (j = 0; j < rc_info_node->unlink_cluster_group_count; j++) {
            /* find exist cluster_group_info */
            if (rc_info_node->unlink_cluster_groups[j].cluster_id == cluster_id) {
                cluster_group_info = &rc_info_node->unlink_cluster_groups[j];
                break;
            }
        }

        /* new cluster_group_info */
        if (j >= rc_info_node->unlink_cluster_group_count) {
            cluster_group_info = &rc_info_node->unlink_cluster_groups[rc_info_node->unlink_cluster_group_count++];
            cluster_group_info->info_count = 0;
            cluster_group_info->group_count = 0;
            cluster_group_info->cluster_id = cluster_id;
        }

        group_info = &cluster_group_info->group_info[cluster_group_info->info_count++];

        /* name server vip */
        len = *((uint32_t *) p);
        if (len <= 0) {
            group_info->ns_vip_text.len = 0;
            return NGX_ERROR;
        }

        group_info->ns_vip_text.len = len - 1;
        p += sizeof(uint32_t);

        group_info->ns_vip_text.data =
            ngx_slab_alloc_locked(rc_ctx->shpool, group_info->ns_vip_text.len);
        if (group_info->ns_vip_text.data == NULL) {
            ngx_http_tfs_expire_and_alloc(group_info->ns_vip_text.data,
                                          group_info->ns_vip_text.len);
        }

        memcpy(group_info->ns_vip_text.data, p, group_info->ns_vip_text.len);

        group_info->group_seq = -1;
        p += len;

        ngx_http_tfs_parse_inet(&group_info->ns_vip_text, &group_info->ns_vip);
    }

    /* use remote cache flag */
    rc_info_node->use_remote_block_cache = *((uint32_t *) p);
    return NGX_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_32__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_8__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_30__ {int code; } ;
struct TYPE_25__ {scalar_t__ block_id; } ;
struct TYPE_28__ {scalar_t__ cluster_id; TYPE_1__ file; } ;
struct TYPE_31__ {int version; TYPE_6__ action; TYPE_4__ fsname; int /*<<< orphan*/  is_raw_update; } ;
struct TYPE_29__ {scalar_t__ cluster_id; TYPE_3__* segment_data; } ;
struct TYPE_33__ {size_t logical_cluster_index; size_t rw_cluster_index; void* state; int /*<<< orphan*/  log; TYPE_7__ r_ctx; TYPE_5__ file; } ;
typedef  TYPE_9__ ngx_http_tfs_t ;
struct TYPE_20__ {size_t logical_cluster_count; size_t unlink_cluster_group_count; TYPE_12__* logical_clusters; TYPE_14__* unlink_cluster_groups; } ;
typedef  TYPE_10__ ngx_http_tfs_rcs_info_t ;
struct TYPE_21__ {scalar_t__ cluster_id; int /*<<< orphan*/  ns_vip; TYPE_8__ ns_vip_text; TYPE_8__ cluster_id_text; int /*<<< orphan*/  access_type; } ;
typedef  TYPE_11__ ngx_http_tfs_physical_cluster_t ;
struct TYPE_22__ {size_t rw_cluster_count; TYPE_11__* rw_clusters; } ;
typedef  TYPE_12__ ngx_http_tfs_logical_cluster_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_inet_t ;
struct TYPE_23__ {TYPE_8__ ns_vip_text; int /*<<< orphan*/  ns_vip; int /*<<< orphan*/  group_seq; } ;
typedef  TYPE_13__ ngx_http_tfs_group_info_t ;
struct TYPE_24__ {scalar_t__ cluster_id; scalar_t__ info_count; int group_count; TYPE_13__* group_info; } ;
typedef  TYPE_14__ ngx_http_tfs_cluster_group_info_t ;
struct TYPE_26__ {scalar_t__ block_id; } ;
struct TYPE_27__ {TYPE_2__ segment_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_ACCESS_READ_AND_WRITE ; 
#define  NGX_HTTP_TFS_ACTION_READ_FILE 131 
#define  NGX_HTTP_TFS_ACTION_REMOVE_FILE 130 
#define  NGX_HTTP_TFS_ACTION_STAT_FILE 129 
#define  NGX_HTTP_TFS_ACTION_WRITE_FILE 128 
 int /*<<< orphan*/  NGX_HTTP_TFS_NO ; 
 void* NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO ; 
 void* NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT ; 
 void* NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ ; 
 void* NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS ; 
 void* NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO ; 
 void* NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT ; 
 void* NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_http_tfs_get_cluster_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_tfs_group_seq_match (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

ngx_int_t
ngx_http_tfs_select_name_server(ngx_http_tfs_t *t,
    ngx_http_tfs_rcs_info_t *rc_info, ngx_http_tfs_inet_t *addr,
    ngx_str_t *addr_text)
{
    uint32_t                            cluster_id, curr_cluster_id, info_count,
                                        curr_block_id;
    ngx_str_t                          *cluster_id_text;
    ngx_uint_t                          i, j;
    ngx_http_tfs_group_info_t          *group_info;
    ngx_http_tfs_logical_cluster_t     *logical_cluster;
    ngx_http_tfs_physical_cluster_t    *physical_cluster;
    ngx_http_tfs_cluster_group_info_t  *cluster_group_info;

    curr_cluster_id = 0;

    if (rc_info == NULL) {
        return NGX_ERROR;
    }
    if (t->r_ctx.version == 1) {
        curr_cluster_id = t->r_ctx.fsname.cluster_id;

    } else if (t->r_ctx.version == 2){
        curr_cluster_id = t->file.cluster_id;
    }

    switch(t->r_ctx.action.code) {
    case NGX_HTTP_TFS_ACTION_STAT_FILE:
    case NGX_HTTP_TFS_ACTION_READ_FILE:
        for (;
             t->logical_cluster_index < rc_info->logical_cluster_count;
             t->logical_cluster_index++)
        {
            logical_cluster =
                           &rc_info->logical_clusters[t->logical_cluster_index];
            for (;
                 t->rw_cluster_index < logical_cluster->rw_cluster_count;
                 t->rw_cluster_index++)
            {
                physical_cluster =
                             &logical_cluster->rw_clusters[t->rw_cluster_index];
                cluster_id_text = &physical_cluster->cluster_id_text;
                cluster_id = ngx_http_tfs_get_cluster_id(cluster_id_text->data);
                if (curr_cluster_id > 0 && cluster_id != curr_cluster_id) {
                    continue;
                }
                ngx_log_debug3(NGX_LOG_DEBUG_HTTP, t->log, 0,
                               "read/stat, select logical cluster "
                               "index: %ui, rw_cluster_index: %ui, "
                               "nameserver: %V",
                               t->logical_cluster_index, t->rw_cluster_index,
                               &physical_cluster->ns_vip_text);
                (*addr) = physical_cluster->ns_vip;
                (*addr_text) = physical_cluster->ns_vip_text;
                return NGX_OK;
            }
            t->rw_cluster_index = 0;
        }

        break;

    case NGX_HTTP_TFS_ACTION_WRITE_FILE:
        if (t->r_ctx.is_raw_update == NGX_HTTP_TFS_NO) {
            for (;
                 t->logical_cluster_index < rc_info->logical_cluster_count;
                 t->logical_cluster_index++)
            {
                logical_cluster =
                               &rc_info->logical_clusters[t->logical_cluster_index];
                for (;
                     t->rw_cluster_index < logical_cluster->rw_cluster_count;
                     t->rw_cluster_index++)
                {
                    physical_cluster =
                                 &logical_cluster->rw_clusters[t->rw_cluster_index];
                    if (physical_cluster->access_type
                        == NGX_HTTP_TFS_ACCESS_READ_AND_WRITE)
                    {
                        /* custom file should ensure writing
                         * all frags in the same cluster */
                        if (curr_cluster_id > 0) {
                            cluster_id_text = &physical_cluster->cluster_id_text;
                            cluster_id =
                                ngx_http_tfs_get_cluster_id(cluster_id_text->data);
                            if (cluster_id != curr_cluster_id) {
                                continue;
                            }
                        }
                        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, t->log, 0,
                                       "write, select logical cluster "
                                       "index: %ui, rw_cluster_index: %ui, "
                                       "nameserver: %V",
                                       t->logical_cluster_index,
                                       t->rw_cluster_index,
                                       &physical_cluster->ns_vip_text);
                        (*addr) = physical_cluster->ns_vip;
                        (*addr_text) = physical_cluster->ns_vip_text;

                        /* check if need get cluster id from ns */
                        if (t->state == NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO) {
                            if (physical_cluster->cluster_id > 0) {
                                t->file.cluster_id = physical_cluster->cluster_id;

                            } else {
                                t->state = NGX_HTTP_TFS_STATE_WRITE_CLUSTER_ID_NS;
                            }
                        }

                        return NGX_OK;
                    }
                }
                t->rw_cluster_index = 0;
            }

            break;
        }

        /* update raw file */
    case NGX_HTTP_TFS_ACTION_REMOVE_FILE:
        for (i = 0; i < rc_info->unlink_cluster_group_count; i++) {
            cluster_group_info = &rc_info->unlink_cluster_groups[i];
            group_info = cluster_group_info->group_info;
            cluster_id = cluster_group_info->cluster_id;
            info_count = cluster_group_info->info_count;

            if ((curr_cluster_id > 0 && cluster_id != curr_cluster_id)
                || info_count < 1)
            {
                continue;
            }

            /* only one cluster, select it */
            if (info_count == 1) {
                (*addr) = group_info[0].ns_vip;
                (*addr_text) = group_info[0].ns_vip_text;
                if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_REMOVE_FILE) {
                    t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO;

                } else if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
                    t->state = NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO;
                }
                ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                               "unlink, select nameserver: %V",
                               &group_info[0].ns_vip_text);
                goto find_logical_cluster_index;
            }

            /* two clusters or more */
            if (cluster_group_info->group_count <= 0) {
                (*addr) = group_info[0].ns_vip;
                (*addr_text) = group_info[0].ns_vip_text;
                if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_REMOVE_FILE) {
                    t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_COUNT;

                } else if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
                    t->state = NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_COUNT;
                }
                return NGX_OK;
            }

            /* if there are two clusters or more but group count is 1, sth wrong in TFS cluster configure */
            if (cluster_group_info->group_count == 1) {
                ngx_log_error(NGX_LOG_ERR, t->log, 0,
                               "unlink, can not select nameserver.");
                return NGX_ERROR;
            }

            for (j = 0; j < info_count; j++) {
                if (group_info[j].group_seq < 0) {
                    (*addr) = group_info[j].ns_vip;
                    (*addr_text) = group_info[j].ns_vip_text;
                    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_REMOVE_FILE) {
                        t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_GROUP_SEQ;

                    } else if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
                        t->state = NGX_HTTP_TFS_STATE_WRITE_GET_GROUP_SEQ;
                    }
                    return NGX_OK;
                }

                if (t->r_ctx.version == 1) {
                    curr_block_id = t->r_ctx.fsname.file.block_id;
                } else {
                    curr_block_id =
                        t->file.segment_data[0].segment_info.block_id;
                }
                if (ngx_http_tfs_group_seq_match(curr_block_id,
                                              cluster_group_info->group_count,
                                              group_info[j].group_seq))
                {
                    (*addr) = group_info[j].ns_vip;
                    (*addr_text) = group_info[j].ns_vip_text;
                    if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_REMOVE_FILE) {
                        t->state = NGX_HTTP_TFS_STATE_REMOVE_GET_BLK_INFO;

                    } else if (t->r_ctx.action.code == NGX_HTTP_TFS_ACTION_WRITE_FILE) {
                        t->state = NGX_HTTP_TFS_STATE_WRITE_GET_BLK_INFO;
                    }

                    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                                   "unlink, select nameserver: %V",
                                   &group_info[j].ns_vip_text);
                    goto find_logical_cluster_index;
                }
            }
        }

        return NGX_ERROR;

find_logical_cluster_index:

        /* find out which logical cluster this addr belongs to
         * so that we can use the right de-dup addr
         */
        t->logical_cluster_index = 0;
        for ( ;
              t->logical_cluster_index < rc_info->logical_cluster_count;
              t->logical_cluster_index++)
        {
            logical_cluster =
                &rc_info->logical_clusters[t->logical_cluster_index];
            t->rw_cluster_index = 0;
            for ( ;
                  t->rw_cluster_index < logical_cluster->rw_cluster_count;
                  t->rw_cluster_index++)
            {
                physical_cluster =
                    &logical_cluster->rw_clusters[t->rw_cluster_index];
                if (*(uint64_t*)(&physical_cluster->ns_vip)
                    == *(uint64_t*)(addr))
                {
                    return NGX_OK;
                }
            }
        }
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "can not find logical cluster index of ns: %V",
                      addr_text);
        return NGX_ERROR;
    }

    return NGX_ERROR;
}
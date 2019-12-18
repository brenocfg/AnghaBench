#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  retry_curr_ns; int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  block_cache_ctx; int /*<<< orphan*/  name_server_addr; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_8__ {int /*<<< orphan*/  block_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  cache_hit; TYPE_1__ segment_info; } ;
typedef  TYPE_3__ ngx_http_tfs_segment_data_t ;
struct TYPE_11__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_4__ ngx_http_tfs_block_cache_key_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_NO_BLOCK_CACHE ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_YES ; 
 int /*<<< orphan*/  ngx_http_tfs_block_cache_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 

void
ngx_http_tfs_remove_block_cache(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    ngx_http_tfs_block_cache_key_t  key;

    key.ns_addr = *((int64_t *)(&t->name_server_addr));
    key.block_id = segment_data->segment_info.block_id;
    ngx_http_tfs_block_cache_remove(&t->block_cache_ctx, t->pool, t->log,
                                    &key, segment_data->cache_hit);

    /* only when cache dirty, need retry current ns */
    if (segment_data->cache_hit != NGX_HTTP_TFS_NO_BLOCK_CACHE) {
        t->retry_curr_ns = NGX_HTTP_TFS_YES;
    }

    segment_data->cache_hit = NGX_HTTP_TFS_NO_BLOCK_CACHE;
}
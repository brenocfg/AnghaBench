#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_4__ {int num; int /*<<< orphan*/  extreme; TYPE_3__* segments; int /*<<< orphan*/  del; int /*<<< orphan*/  query; int /*<<< orphan*/  insert; int /*<<< orphan*/  build; int /*<<< orphan*/  cmp; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ ngx_segment_tree_t ;
typedef  int /*<<< orphan*/  ngx_segment_node_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_MAX_UINT32_VALUE ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_segment_tree_build ; 
 int /*<<< orphan*/  ngx_segment_tree_delete ; 
 int /*<<< orphan*/  ngx_segment_tree_insert ; 
 int /*<<< orphan*/  ngx_segment_tree_min ; 
 int /*<<< orphan*/  ngx_segment_tree_query ; 

ngx_int_t
ngx_segment_tree_init(ngx_segment_tree_t *tree, ngx_uint_t num,
    ngx_pool_t *pool)
{
    tree->segments = ngx_pcalloc(pool,
                                ((num + 1) << 2) * sizeof(ngx_segment_node_t));
    if (tree->segments == NULL) {
        return NGX_ERROR;
    }

    tree->extreme = NGX_MAX_UINT32_VALUE;
    tree->pool = pool;
    tree->num = num;

    tree->cmp = ngx_segment_tree_min;
    tree->build = ngx_segment_tree_build;
    tree->insert = ngx_segment_tree_insert;
    tree->query = ngx_segment_tree_query;
    tree->del = ngx_segment_tree_delete;

    tree->segments[0].key = tree->extreme;
    return NGX_OK;
}
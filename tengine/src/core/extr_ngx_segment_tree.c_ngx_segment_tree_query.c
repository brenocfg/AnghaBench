#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* cmp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * segments; } ;
typedef  TYPE_1__ ngx_segment_tree_t ;
typedef  int /*<<< orphan*/  ngx_segment_node_t ;
typedef  size_t ngx_int_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_segment_node_t *
ngx_segment_tree_query(ngx_segment_tree_t *tree, ngx_int_t index, ngx_int_t l,
    ngx_int_t r, ngx_int_t ll, ngx_int_t rr)
{
    ngx_int_t  child, mid;
    ngx_segment_node_t *l_node, *r_node;

    if (ll > rr) {
        return &tree->segments[0];
    }

    if (l == ll && r == rr) {
        return &tree->segments[index];
    }

    child = index << 1;
    mid = (l + r) >> 1;

    if (rr <= mid) {
        return ngx_segment_tree_query(tree, child, l, mid, ll, rr);

    } else if (ll > mid) {
        return ngx_segment_tree_query(tree, child + 1, mid + 1, r, ll, rr);
    }

    l_node = ngx_segment_tree_query(tree, child, l, mid, ll, mid);
    r_node = ngx_segment_tree_query(tree, child + 1, mid + 1, r, mid + 1, rr);

    if (tree->cmp(l_node, r_node) > 0) {
        return l_node;
    }

    return r_node;
}
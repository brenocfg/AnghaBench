#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ key; } ;
typedef  TYPE_1__ ngx_segment_node_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */

__attribute__((used)) static ngx_int_t
ngx_segment_tree_min(ngx_segment_node_t *one, ngx_segment_node_t *two)
{
    return two->key - one->key;
}
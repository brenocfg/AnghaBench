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
struct TYPE_3__ {int /*<<< orphan*/ * idx; scalar_t__ i_idx_max; scalar_t__ i_idx; } ;
typedef  TYPE_1__ demux_index_t ;

/* Variables and functions */

__attribute__((used)) static void demux_IndexInit( demux_index_t *p_idx )
{
    p_idx->i_idx = 0;
    p_idx->i_idx_max = 0;
    p_idx->idx = NULL;
}
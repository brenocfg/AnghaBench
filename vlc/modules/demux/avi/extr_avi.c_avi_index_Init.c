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
struct TYPE_3__ {int /*<<< orphan*/ * p_entry; scalar_t__ i_max; scalar_t__ i_size; } ;
typedef  TYPE_1__ avi_index_t ;

/* Variables and functions */

__attribute__((used)) static void avi_index_Init( avi_index_t *p_index )
{
    p_index->i_size  = 0;
    p_index->i_max   = 0;
    p_index->p_entry = NULL;
}
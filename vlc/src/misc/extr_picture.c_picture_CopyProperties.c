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
struct TYPE_4__ {int /*<<< orphan*/  b_top_field_first; int /*<<< orphan*/  i_nb_fields; int /*<<< orphan*/  b_progressive; int /*<<< orphan*/  b_still; int /*<<< orphan*/  b_force; int /*<<< orphan*/  date; } ;
typedef  TYPE_1__ picture_t ;

/* Variables and functions */

void picture_CopyProperties( picture_t *p_dst, const picture_t *p_src )
{
    p_dst->date = p_src->date;
    p_dst->b_force = p_src->b_force;
    p_dst->b_still = p_src->b_still;

    p_dst->b_progressive = p_src->b_progressive;
    p_dst->i_nb_fields = p_src->i_nb_fields;
    p_dst->b_top_field_first = p_src->b_top_field_first;
}
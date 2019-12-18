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
struct TYPE_4__ {int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_nb_samples; int /*<<< orphan*/  p_next; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static void BlockMetaCopy( block_t *restrict out, const block_t *in )
{
    out->p_next    = in->p_next;
    out->i_nb_samples = in->i_nb_samples;
    out->i_dts     = in->i_dts;
    out->i_pts     = in->i_pts;
    out->i_flags   = in->i_flags;
    out->i_length  = in->i_length;
}
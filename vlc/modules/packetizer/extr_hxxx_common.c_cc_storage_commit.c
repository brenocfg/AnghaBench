#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  next; int /*<<< orphan*/  current; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_1__ cc_storage_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  cc_Flush (int /*<<< orphan*/ *) ; 

void cc_storage_commit( cc_storage_t *p_ccs, block_t *p_pic )
{
    p_ccs->i_pts = p_pic->i_pts;
    p_ccs->i_dts = p_pic->i_dts;
    p_ccs->i_flags = p_pic->i_flags;
    p_ccs->current = p_ccs->next;
    cc_Flush( &p_ccs->next );
}
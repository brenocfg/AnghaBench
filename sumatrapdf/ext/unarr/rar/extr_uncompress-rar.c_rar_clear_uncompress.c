#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  filters; int /*<<< orphan*/  ppmd7_context; } ;
struct TYPE_4__ {TYPE_1__ v3; } ;
struct ar_archive_rar_uncomp {int version; TYPE_2__ state; int /*<<< orphan*/  lzss; } ;

/* Variables and functions */
 int /*<<< orphan*/  Ppmd7_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gSzAlloc ; 
 int /*<<< orphan*/  lzss_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rar_clear_filters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rar_free_codes (struct ar_archive_rar_uncomp*) ; 

void rar_clear_uncompress(struct ar_archive_rar_uncomp *uncomp)
{
    if (!uncomp->version)
        return;
    rar_free_codes(uncomp);
    lzss_cleanup(&uncomp->lzss);
    if (uncomp->version == 3) {
        Ppmd7_Free(&uncomp->state.v3.ppmd7_context, &gSzAlloc);
        rar_clear_filters(&uncomp->state.v3.filters);
    }
    uncomp->version = 0;
}
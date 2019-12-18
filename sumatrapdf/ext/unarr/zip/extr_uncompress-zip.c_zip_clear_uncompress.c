#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ar_archive_zip_uncomp {int initialized; int /*<<< orphan*/  (* clear_state ) (struct ar_archive_zip_uncomp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ar_archive_zip_uncomp*) ; 

void zip_clear_uncompress(struct ar_archive_zip_uncomp *uncomp)
{
    if (!uncomp->initialized)
        return;
    uncomp->clear_state(uncomp);
    uncomp->initialized = false;
}
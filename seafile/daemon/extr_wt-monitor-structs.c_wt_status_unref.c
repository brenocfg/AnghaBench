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
struct TYPE_4__ {scalar_t__ ref_count; } ;
typedef  TYPE_1__ WTStatus ;

/* Variables and functions */
 int /*<<< orphan*/  free_wt_status (TYPE_1__*) ; 

void
wt_status_unref (WTStatus *status)
{
    if (!status) return;

    if (--(status->ref_count) <= 0)
        free_wt_status (status);
}
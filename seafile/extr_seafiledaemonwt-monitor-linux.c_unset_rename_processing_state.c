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
struct TYPE_3__ {int /*<<< orphan*/  processing; int /*<<< orphan*/ * old_path; scalar_t__ last_cookie; } ;
typedef  TYPE_1__ RenameInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static void
unset_rename_processing_state (RenameInfo *info)
{
    info->last_cookie = 0;
    g_free (info->old_path);
    info->old_path = NULL;
    info->processing = FALSE;
}
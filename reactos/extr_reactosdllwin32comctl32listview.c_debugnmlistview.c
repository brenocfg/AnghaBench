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
struct TYPE_3__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  ptAction; int /*<<< orphan*/  uChanged; int /*<<< orphan*/  uOldState; int /*<<< orphan*/  uNewState; int /*<<< orphan*/  iSubItem; int /*<<< orphan*/  iItem; } ;
typedef  TYPE_1__ NMLISTVIEW ;

/* Variables and functions */
 char const* wine_dbg_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char* debugnmlistview(const NMLISTVIEW *plvnm)
{
    if (!plvnm) return "(null)";
    return wine_dbg_sprintf("iItem=%d, iSubItem=%d, uNewState=0x%x,"
	         " uOldState=0x%x, uChanged=0x%x, ptAction=%s, lParam=%ld",
	         plvnm->iItem, plvnm->iSubItem, plvnm->uNewState, plvnm->uOldState,
		 plvnm->uChanged, wine_dbgstr_point(&plvnm->ptAction), plvnm->lParam);
}
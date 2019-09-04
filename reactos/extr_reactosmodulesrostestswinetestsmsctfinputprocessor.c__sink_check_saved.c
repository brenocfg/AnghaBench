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
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * FOCUS_IGNORE ; 
 int /*<<< orphan*/ * FOCUS_SAVE ; 
 int /*<<< orphan*/  _sink_check_ok (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int expected_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_FirstPrevFocus ; 
 int /*<<< orphan*/ * test_LastCurrentFocus ; 
 int /*<<< orphan*/  winetest_ok (int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _sink_check_saved(INT *sink, ITfDocumentMgr *PrevFocus, ITfDocumentMgr *CurrentFocus, const CHAR* name)
{
    int count = expected_count(sink);
    _sink_check_ok(sink, name);
    if (PrevFocus != FOCUS_IGNORE && count != 0)
        winetest_ok(PrevFocus == test_FirstPrevFocus, "%s expected prev focus %p got %p\n", name, PrevFocus, test_FirstPrevFocus);
    if (CurrentFocus != FOCUS_IGNORE && count != 0)
        winetest_ok(CurrentFocus == test_LastCurrentFocus, "%s expected current focus %p got %p\n", name, CurrentFocus, test_LastCurrentFocus);
    test_FirstPrevFocus = FOCUS_SAVE;
    test_LastCurrentFocus = FOCUS_SAVE;
}
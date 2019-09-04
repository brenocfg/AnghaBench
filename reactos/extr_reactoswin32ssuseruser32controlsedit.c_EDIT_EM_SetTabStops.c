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
struct TYPE_4__ {int style; int tabs_count; int /*<<< orphan*/ * tabs; } ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_1__*) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static BOOL EDIT_EM_SetTabStops(EDITSTATE *es, INT count, const INT *tabs)
{
	if (!(es->style & ES_MULTILINE))
		return FALSE;
        HeapFree(GetProcessHeap(), 0, es->tabs);
	es->tabs_count = count;
	if (!count)
		es->tabs = NULL;
	else {
		es->tabs = HeapAlloc(GetProcessHeap(), 0, count * sizeof(INT));
#ifdef __REACTOS__
        /* ReactOS r33503 */
        if (es->tabs == NULL)
        {
            es->tabs_count = 0;
            return FALSE;
        }
#endif
		memcpy(es->tabs, tabs, count * sizeof(INT));
	}
	EDIT_InvalidateUniscribeData(es);
	return TRUE;
}
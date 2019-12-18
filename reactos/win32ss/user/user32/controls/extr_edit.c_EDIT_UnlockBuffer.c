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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int lock_count; int /*<<< orphan*/ * text; scalar_t__ hloc32W; scalar_t__ hloc32A; int /*<<< orphan*/  hwndSelf; scalar_t__ hlocapp; } ;
typedef  scalar_t__ HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 int /*<<< orphan*/ * LocalLock (scalar_t__) ; 
 scalar_t__ LocalReAlloc (scalar_t__,scalar_t__,int) ; 
 scalar_t__ LocalSize (scalar_t__) ; 
 int /*<<< orphan*/  LocalUnlock (scalar_t__) ; 
 scalar_t__ ROUND_TO_GROW (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_text_length (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_UnlockBuffer(EDITSTATE *es, BOOL force)
{
        if (es->hlocapp) return;

	/* Edit window might be already destroyed */
	if(!IsWindow(es->hwndSelf))
	{
	    WARN("edit hwnd %p already destroyed\n", es->hwndSelf);
	    return;
	}

	if (!es->lock_count) {
		ERR("lock_count == 0 ... please report\n");
		return;
	}
	if (!es->text) {
		ERR("es->text == 0 ... please report\n");
		return;
	}

	if (force || (es->lock_count == 1)) {
	    if (es->hloc32W) {
		UINT countA = 0;
		UINT countW = get_text_length(es) + 1;

		if(es->hloc32A)
		{
		    UINT countA_new = WideCharToMultiByte(CP_ACP, 0, es->text, countW, NULL, 0, NULL, NULL);
		    TRACE("Synchronizing with 32-bit ANSI buffer\n");
		    TRACE("%d WCHARs translated to %d bytes\n", countW, countA_new);
		    countA = LocalSize(es->hloc32A);
		    if(countA_new > countA)
		    {
			HLOCAL hloc32A_new;
			UINT alloc_size = ROUND_TO_GROW(countA_new);
			TRACE("Resizing 32-bit ANSI buffer from %d to %d bytes\n", countA, alloc_size);
			hloc32A_new = LocalReAlloc(es->hloc32A, alloc_size, LMEM_MOVEABLE | LMEM_ZEROINIT);
			if(hloc32A_new)
			{
			    es->hloc32A = hloc32A_new;
			    countA = LocalSize(hloc32A_new);
			    TRACE("Real new size %d bytes\n", countA);
			}
			else
			    WARN("FAILED! Will synchronize partially\n");
		    }
		    WideCharToMultiByte(CP_ACP, 0, es->text, countW,
                                        LocalLock(es->hloc32A), countA, NULL, NULL);
                    LocalUnlock(es->hloc32A);
		}

		LocalUnlock(es->hloc32W);
		es->text = NULL;
	    }
	    else {
		ERR("no buffer ... please report\n");
		return;
	    }
	}
	es->lock_count--;
}
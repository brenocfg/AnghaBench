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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_3__ {int buffer_size; int /*<<< orphan*/  lock_count; scalar_t__ hloc32W; int /*<<< orphan*/ * text; scalar_t__ hloc32A; scalar_t__ hlocapp; } ;
typedef  scalar_t__ HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 void* LocalLock (scalar_t__) ; 
 scalar_t__ LocalReAlloc (scalar_t__,int,int) ; 
 int LocalSize (scalar_t__) ; 
 int /*<<< orphan*/  LocalUnlock (scalar_t__) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int ROUND_TO_GROW (int) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static void EDIT_LockBuffer(EDITSTATE *es)
{
        if (es->hlocapp) return;

	if (!es->text) {

#ifdef __REACTOS__
/* FIXME: What is this ? */
	    CHAR *textA = NULL; // ReactOS Hacked! r45670
	    //UINT countA = 0;

	    if(es->hloc32W)
	    {
		if(es->hloc32A)
		{
		    TRACE("Synchronizing with 32-bit ANSI buffer\n");
		    textA = LocalLock(es->hloc32A);
		    //countA = strlen(textA) + 1;
		}
	    }
	    else {
		ERR("no buffer ... please report\n");
		return;
	    }

	    if (textA) //// ReactOS
	    {
#else
	    if(!es->hloc32W) return;

            if(es->hloc32A)
            {
                CHAR *textA = LocalLock(es->hloc32A);
#endif
		HLOCAL hloc32W_new;
		UINT countW_new = MultiByteToWideChar(CP_ACP, 0, textA, -1, NULL, 0);
		if(countW_new > es->buffer_size + 1)
		{
		    UINT alloc_size = ROUND_TO_GROW(countW_new * sizeof(WCHAR));
		    TRACE("Resizing 32-bit UNICODE buffer from %d+1 to %d WCHARs\n", es->buffer_size, countW_new);
		    hloc32W_new = LocalReAlloc(es->hloc32W, alloc_size, LMEM_MOVEABLE | LMEM_ZEROINIT);
		    if(hloc32W_new)
		    {
			es->hloc32W = hloc32W_new;
			es->buffer_size = LocalSize(hloc32W_new)/sizeof(WCHAR) - 1;
			TRACE("Real new size %d+1 WCHARs\n", es->buffer_size);
		    }
		    else
			WARN("FAILED! Will synchronize partially\n");
		}
                es->text = LocalLock(es->hloc32W);
		MultiByteToWideChar(CP_ACP, 0, textA, -1, es->text, es->buffer_size + 1);
                LocalUnlock(es->hloc32A);
	    }
	    else es->text = LocalLock(es->hloc32W);
	}
	es->lock_count++;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int style; void* hloc32A; void* hloc32W; int buffer_size; int /*<<< orphan*/  flags; scalar_t__ selection_end; scalar_t__ selection_start; scalar_t__ y_offset; scalar_t__ x_offset; int /*<<< orphan*/ * hlocapp; scalar_t__ is_unicode; } ;
typedef  int INT ;
typedef  void* HLOCAL ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  EDIT_BuildLineDefs_ML (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_EM_EmptyUndoBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_LockBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_UnlockBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_MODIFIED ; 
 int /*<<< orphan*/  EF_UPDATE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int ES_MULTILINE ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 void* LocalAlloc (int,int) ; 
 int /*<<< orphan*/  LocalFree (void*) ; 
 void* LocalLock (void*) ; 
 int LocalSize (void*) ; 
 int /*<<< orphan*/  LocalUnlock (void*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  get_text_length (TYPE_1__*) ; 
 int /*<<< orphan*/  text_buffer_changed (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_EM_SetHandle(EDITSTATE *es, HLOCAL hloc)
{
	if (!(es->style & ES_MULTILINE))
		return;

	if (!hloc) {
		WARN("called with NULL handle\n");
		return;
	}

	EDIT_UnlockBuffer(es, TRUE);

	if(es->is_unicode)
	{
	    if(es->hloc32A)
	    {
		LocalFree(es->hloc32A);
		es->hloc32A = NULL;
	    }
	    es->hloc32W = hloc;
	}
	else
	{
	    INT countW, countA;
	    HLOCAL hloc32W_new;
	    WCHAR *textW;
	    CHAR *textA;

	    countA = LocalSize(hloc);
	    textA = LocalLock(hloc);
	    countW = MultiByteToWideChar(CP_ACP, 0, textA, countA, NULL, 0);
	    if(!(hloc32W_new = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, countW * sizeof(WCHAR))))
	    {
		ERR("Could not allocate new unicode buffer\n");
		return;
	    }
	    textW = LocalLock(hloc32W_new);
	    MultiByteToWideChar(CP_ACP, 0, textA, countA, textW, countW);
	    LocalUnlock(hloc32W_new);
	    LocalUnlock(hloc);

	    if(es->hloc32W)
		LocalFree(es->hloc32W);

	    es->hloc32W = hloc32W_new;
	    es->hloc32A = hloc;
	}

	es->buffer_size = LocalSize(es->hloc32W)/sizeof(WCHAR) - 1;

        /* The text buffer handle belongs to the control */
        es->hlocapp = NULL;

	EDIT_LockBuffer(es);
        text_buffer_changed(es);

	es->x_offset = es->y_offset = 0;
	es->selection_start = es->selection_end = 0;
	EDIT_EM_EmptyUndoBuffer(es);
	es->flags &= ~EF_MODIFIED;
	es->flags &= ~EF_UPDATE;
	EDIT_BuildLineDefs_ML(es, 0, get_text_length(es), 0, NULL);
	EDIT_UpdateText(es, NULL, TRUE);
	EDIT_EM_ScrollCaret(es);
	/* force scroll info update */
	EDIT_UpdateScrollInfo(es);
}
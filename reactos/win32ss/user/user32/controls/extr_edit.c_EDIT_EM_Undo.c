#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int style; int /*<<< orphan*/ * undo_text; scalar_t__ undo_insert_count; scalar_t__ undo_position; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_EmptyUndoBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int ES_MULTILINE ; 
 int ES_READONLY ; 
 int FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL EDIT_EM_Undo(EDITSTATE *es)
{
	INT ulength;
	LPWSTR utext;

	/* As per MSDN spec, for a single-line edit control,
	   the return value is always TRUE */
	if( es->style & ES_READONLY )
            return !(es->style & ES_MULTILINE);

	ulength = strlenW(es->undo_text);

	utext = HeapAlloc(GetProcessHeap(), 0, (ulength + 1) * sizeof(WCHAR));
#ifdef __REACTOS__
	/* ReactOS r33503 */
	if (utext == NULL) 
		return FALSE;
#endif

	strcpyW(utext, es->undo_text);

	TRACE("before UNDO:insertion length = %d, deletion buffer = %s\n",
		     es->undo_insert_count, debugstr_w(utext));

	EDIT_EM_SetSel(es, es->undo_position, es->undo_position + es->undo_insert_count, FALSE);
	EDIT_EM_EmptyUndoBuffer(es);
	EDIT_EM_ReplaceSel(es, TRUE, utext, TRUE, TRUE);
	EDIT_EM_SetSel(es, es->undo_position, es->undo_position + es->undo_insert_count, FALSE);
        /* send the notification after the selection start and end are set */
        EDIT_NOTIFY_PARENT(es, EN_CHANGE);
	EDIT_EM_ScrollCaret(es);
	HeapFree(GetProcessHeap(), 0, utext);

	TRACE("after UNDO:insertion length = %d, deletion buffer = %s\n",
			es->undo_insert_count, debugstr_w(es->undo_text));
	return TRUE;
}
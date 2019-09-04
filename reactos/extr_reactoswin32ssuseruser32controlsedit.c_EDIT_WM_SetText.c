#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int flags; int style; scalar_t__ hwndListBox; scalar_t__ x_offset; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_EM_ScrollCaret (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_EM_SetSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_1__*) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_UpdateScrollInfo (TYPE_1__*) ; 
 int EF_MODIFIED ; 
 int EF_UPDATE ; 
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  EN_UPDATE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * empty_stringW ; 

__attribute__((used)) static void EDIT_WM_SetText(EDITSTATE *es, LPCWSTR text, BOOL unicode)
{
    LPWSTR textW = NULL;
    if (!unicode && text)
    {
	LPCSTR textA = (LPCSTR)text;
	INT countW = MultiByteToWideChar(CP_ACP, 0, textA, -1, NULL, 0);
        textW = HeapAlloc(GetProcessHeap(), 0, countW * sizeof(WCHAR));
	if (textW)
	    MultiByteToWideChar(CP_ACP, 0, textA, -1, textW, countW);
	text = textW;
    }

    if (es->flags & EF_UPDATE)
	/* fixed this bug once; complain if we see it about to happen again. */
	ERR("SetSel may generate UPDATE message whose handler may reset "
	    "selection.\n");

    EDIT_EM_SetSel(es, 0, (UINT)-1, FALSE);
    if (text) 
    {
	TRACE("%s\n", debugstr_w(text));
	EDIT_EM_ReplaceSel(es, FALSE, text, FALSE, FALSE);
	if(!unicode)
	    HeapFree(GetProcessHeap(), 0, textW);
    } 
    else 
    {
	TRACE("<NULL>\n");
	EDIT_EM_ReplaceSel(es, FALSE, empty_stringW, FALSE, FALSE);
    }
    es->x_offset = 0;
    es->flags &= ~EF_MODIFIED;
    EDIT_EM_SetSel(es, 0, 0, FALSE);

    /* Send the notification after the selection start and end have been set
     * edit control doesn't send notification on WM_SETTEXT
     * if it is multiline, or it is part of combobox
     */
    if( !((es->style & ES_MULTILINE) || es->hwndListBox))
    {
        EDIT_NOTIFY_PARENT(es, EN_UPDATE);
        EDIT_NOTIFY_PARENT(es, EN_CHANGE);
    }
    EDIT_EM_ScrollCaret(es);
    EDIT_UpdateScrollInfo(es);    
    EDIT_InvalidateUniscribeData(es);
}
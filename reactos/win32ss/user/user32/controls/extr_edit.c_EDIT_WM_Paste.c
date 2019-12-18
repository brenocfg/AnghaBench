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
struct TYPE_4__ {int style; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ES_PASSWORD ; 
 int ES_READONLY ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_stringW ; 

__attribute__((used)) static void EDIT_WM_Paste(EDITSTATE *es)
{
	HGLOBAL hsrc;
	LPWSTR src;

	/* Protect read-only edit control from modification */
	if(es->style & ES_READONLY)
	    return;

	OpenClipboard(es->hwndSelf);
	if ((hsrc = GetClipboardData(CF_UNICODETEXT))) {
		src = GlobalLock(hsrc);
		EDIT_EM_ReplaceSel(es, TRUE, src, TRUE, TRUE);
		GlobalUnlock(hsrc);
	}
        else if (es->style & ES_PASSWORD) {
            /* clear selected text in password edit box even with empty clipboard */
            EDIT_EM_ReplaceSel(es, TRUE, empty_stringW, TRUE, TRUE);
        }
	CloseClipboard();
}
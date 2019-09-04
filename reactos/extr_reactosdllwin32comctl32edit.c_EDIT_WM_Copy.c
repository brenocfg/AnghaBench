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
struct TYPE_3__ {scalar_t__ text; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; } ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  EmptyClipboard () ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int,int) ; 
 scalar_t__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_WM_Copy(EDITSTATE *es)
{
	INT s = min(es->selection_start, es->selection_end);
	INT e = max(es->selection_start, es->selection_end);
	HGLOBAL hdst;
	LPWSTR dst;
	DWORD len;

	if (e == s) return;

	len = e - s;
	hdst = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (len + 1) * sizeof(WCHAR));
	dst = GlobalLock(hdst);
	memcpy(dst, es->text + s, len * sizeof(WCHAR));
	dst[len] = 0; /* ensure 0 termination */
	TRACE("%s\n", debugstr_w(dst));
	GlobalUnlock(hdst);
	OpenClipboard(es->hwndSelf);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hdst);
	CloseClipboard();
}
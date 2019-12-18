#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int style; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/ * hwndListBox; scalar_t__ wheelDeltaRemainder; int /*<<< orphan*/  selection_end; int /*<<< orphan*/  selection_start; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int CBS_DROPDOWN ; 
 int CBS_SIMPLE ; 
 int /*<<< orphan*/  DestroyCaret () ; 
 int /*<<< orphan*/  EDIT_InvalidateText (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_NOTIFY_PARENT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF_FOCUSED ; 
 int /*<<< orphan*/  EN_KILLFOCUS ; 
 int ES_NOHIDESEL ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int GetWindowLong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_CBLOSTTEXTFOCUS ; 

__attribute__((used)) static LRESULT EDIT_WM_KillFocus(EDITSTATE *es)
{
	HWND hCombo;
	LONG lStyles;

	es->flags &= ~EF_FOCUSED;
	DestroyCaret();
	if(!(es->style & ES_NOHIDESEL))
		EDIT_InvalidateText(es, es->selection_start, es->selection_end);

	/* throw away left over scroll when we lose focus */
	es->wheelDeltaRemainder = 0;

	if (es->hwndListBox == NULL)
		EDIT_NOTIFY_PARENT(es, EN_KILLFOCUS);
	else
	{ /* send the undocumented WM_CBLOSTTEXTFOCUS message to combobox */
		hCombo = GetParent(es->hwndSelf);
		lStyles = GetWindowLong(hCombo, GWL_STYLE);
		if ((lStyles & CBS_DROPDOWN) || (lStyles & CBS_SIMPLE))
			SendMessage(hCombo, WM_CBLOSTTEXTFOCUS, 0, 0);
	}

	return 0;
}
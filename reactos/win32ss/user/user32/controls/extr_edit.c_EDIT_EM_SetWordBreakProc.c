#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* word_break_proc; int style; } ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_BuildLineDefs_ML (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ES_AUTOHSCROLL ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_text_length (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_EM_SetWordBreakProc(EDITSTATE *es, void *wbp)
{
	if (es->word_break_proc == wbp)
		return;

	es->word_break_proc = wbp;

	if ((es->style & ES_MULTILINE) && !(es->style & ES_AUTOHSCROLL)) {
		EDIT_BuildLineDefs_ML(es, 0, get_text_length(es), 0, NULL);
		EDIT_UpdateText(es, NULL, TRUE);
	}
}
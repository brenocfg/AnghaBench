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
struct TYPE_6__ {int style; } ;
typedef  int INT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_ML_InvalidateText (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  EDIT_SL_InvalidateText (TYPE_1__*,int,int) ; 
 int ES_MULTILINE ; 
 int get_text_length (TYPE_1__*) ; 

__attribute__((used)) static void EDIT_InvalidateText(EDITSTATE *es, INT start, INT end)
{
	if (end == start)
		return;

	if (end == -1)
		end = get_text_length(es);

	if (end < start) {
	    INT tmp = start;
	    start = end;
	    end = tmp;
	}

	if (es->style & ES_MULTILINE)
		EDIT_ML_InvalidateText(es, start, end);
	else
		EDIT_SL_InvalidateText(es, start, end);
}
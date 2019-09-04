#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ idCommand; } ;
struct TYPE_4__ {scalar_t__ nNumButtons; TYPE_2__* buttons; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,scalar_t__,...) ; 

__attribute__((used)) static INT
TOOLBAR_GetButtonIndex (const TOOLBAR_INFO *infoPtr, INT idCommand, BOOL CommandIsIndex)
{
    TBUTTON_INFO *btnPtr;
    INT i;

    if (CommandIsIndex) {
	TRACE("command is really index command=%d\n", idCommand);
	if (idCommand >= infoPtr->nNumButtons) return -1;
	return idCommand;
    }
    btnPtr = infoPtr->buttons;
    for (i = 0; i < infoPtr->nNumButtons; i++, btnPtr++) {
	if (btnPtr->idCommand == idCommand) {
	    TRACE("command=%d index=%d\n", idCommand, i);
	    return i;
	}
    }
    TRACE("no index found for command=%d\n", idCommand);
    return -1;
}
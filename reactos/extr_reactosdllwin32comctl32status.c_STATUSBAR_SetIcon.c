#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hIcon; int /*<<< orphan*/  bound; } ;
struct TYPE_7__ {int numParts; TYPE_2__* parts; int /*<<< orphan*/  Self; scalar_t__ simple; TYPE_1__ part0; } ;
struct TYPE_6__ {scalar_t__ hIcon; int /*<<< orphan*/  bound; } ;
typedef  TYPE_3__ STATUS_INFO ;
typedef  int INT ;
typedef  scalar_t__ HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
STATUSBAR_SetIcon (STATUS_INFO *infoPtr, INT nPart, HICON hIcon)
{
    if ((nPart < -1) || (nPart >= infoPtr->numParts))
	return FALSE;

    TRACE("setting part %d\n", nPart);

    /* FIXME: MSDN says "if nPart is -1, the status bar is assumed simple" */
    if (nPart == -1) {
	if (infoPtr->part0.hIcon == hIcon) /* same as - no redraw */
	    return TRUE;
	infoPtr->part0.hIcon = hIcon;
	if (infoPtr->simple)
            InvalidateRect(infoPtr->Self, &infoPtr->part0.bound, FALSE);
    } else {
	if (infoPtr->parts[nPart].hIcon == hIcon) /* same as - no redraw */
	    return TRUE;

	infoPtr->parts[nPart].hIcon = hIcon;
	if (!(infoPtr->simple))
            InvalidateRect(infoPtr->Self, &infoPtr->parts[nPart].bound, FALSE);
    }
    return TRUE;
}
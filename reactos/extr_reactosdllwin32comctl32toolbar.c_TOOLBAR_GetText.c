#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int iString; } ;
struct TYPE_5__ {int nNumStrings; int /*<<< orphan*/ ** strings; } ;
typedef  TYPE_1__ TOOLBAR_INFO ;
typedef  TYPE_2__ TBUTTON_INFO ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IS_INTRESOURCE (int) ; 

__attribute__((used)) static LPWSTR
TOOLBAR_GetText(const TOOLBAR_INFO *infoPtr, const TBUTTON_INFO *btnPtr)
{
    LPWSTR lpText = NULL;

    /* NOTE: iString == -1 is undocumented */
    if (!IS_INTRESOURCE(btnPtr->iString) && (btnPtr->iString != -1))
        lpText = (LPWSTR)btnPtr->iString;
    else if ((btnPtr->iString >= 0) && (btnPtr->iString < infoPtr->nNumStrings))
        lpText = infoPtr->strings[btnPtr->iString];

    return lpText;
}
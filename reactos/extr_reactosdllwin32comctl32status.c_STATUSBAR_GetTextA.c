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
struct TYPE_5__ {int style; scalar_t__ text; } ;
struct TYPE_4__ {size_t numParts; TYPE_2__* parts; TYPE_2__ part0; scalar_t__ simple; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ STATUSWINDOWPART ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  size_t INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ MAKELONG (scalar_t__,int) ; 
 int SBT_OWNERDRAW ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
STATUSBAR_GetTextA (STATUS_INFO *infoPtr, INT nPart, LPSTR buf)
{
    STATUSWINDOWPART *part;
    LRESULT result;

    TRACE("part %d\n", nPart);

    /* MSDN says: "simple parts use index of 0", so this check is ok. */
    if (nPart < 0 || nPart >= infoPtr->numParts) return 0;

    if (infoPtr->simple)
	part = &infoPtr->part0;
    else
	part = &infoPtr->parts[nPart];

    if (part->style & SBT_OWNERDRAW)
	result = (LRESULT)part->text;
    else {
        DWORD len = part->text ? WideCharToMultiByte( CP_ACP, 0, part->text, -1,
                                                      NULL, 0, NULL, NULL ) - 1 : 0;
        result = MAKELONG( len, part->style );
        if (part->text && buf)
            WideCharToMultiByte( CP_ACP, 0, part->text, -1, buf, len+1, NULL, NULL );
    }
    return result;
}
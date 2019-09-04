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
typedef  char WCHAR ;
struct TYPE_3__ {scalar_t__ cy; scalar_t__ cx; } ;
typedef  char* LPWSTR ;
typedef  TYPE_1__* LPSIZE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SL_LEFTMARGIN ; 
 int /*<<< orphan*/  TRUE ; 
 int max (int,int) ; 

__attribute__((used)) static BOOL SYSLINK_WrapLine (LPWSTR Text, WCHAR BreakChar, int x, int *LineLen,
                             int nFit, LPSIZE Extent)
{
    int i;

    for (i = 0; i < nFit; i++) if (Text[i] == '\n') break;

    if (i == *LineLen) return FALSE;

    /* check if we're in the middle of a word */
    if (Text[i] != '\n' && Text[i] != BreakChar)
    {
        /* search for the beginning of the word */
        while (i && Text[i - 1] != BreakChar) i--;

        if (i == 0)
        {
            Extent->cx = 0;
            Extent->cy = 0;
            if (x == SL_LEFTMARGIN) i = max( nFit, 1 );
        }
    }
    *LineLen = i;
    return TRUE;
}
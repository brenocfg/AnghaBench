#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int KdbNumberOfColsTerminal ; 
 int KdbNumberOfRowsTerminal ; 
 scalar_t__ memrchr (scalar_t__,char,int) ; 

PCHAR
CountOnePageUp(PCHAR Buffer, ULONG BufLength, PCHAR pCurPos)
{
    PCHAR p;
    // p0 is initial guess of Page Start
    ULONG p0len = KdbNumberOfRowsTerminal * KdbNumberOfColsTerminal;
    PCHAR p0 = pCurPos - p0len;
    PCHAR prev_p = p0, p1;
    ULONG j;

    if (pCurPos < Buffer)
        pCurPos = Buffer;
    ASSERT(pCurPos <= Buffer + BufLength);

    p = memrchr(p0, '\n', p0len);
    if (NULL == p)
        p = p0;
    for (j = KdbNumberOfRowsTerminal; j--; )
    {
        int linesCnt;
        p1 = memrchr(p0, '\n', p-p0);
        prev_p = p;
        p = p1;
        if (NULL == p)
        {
            p = prev_p;
            if (NULL == p)
                p = p0;
            break;
        }
        linesCnt = (KdbNumberOfColsTerminal+prev_p-p-2) / KdbNumberOfColsTerminal;
        if (linesCnt > 1)
            j -= linesCnt-1;
    }

    ASSERT(p != 0);
    ++p;
    return p;
}
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
struct TYPE_5__ {int nText; TYPE_1__* Blocks; } ;
struct TYPE_4__ {scalar_t__ nSkip; scalar_t__ nChars; int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_1__* PDOC_TEXTBLOCK ;
typedef  TYPE_2__ DOC_ITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL SYSLINK_PtInDocItem (const DOC_ITEM *DocItem, POINT pt)
{
    PDOC_TEXTBLOCK bl;
    int n;

    bl = DocItem->Blocks;
    if (bl != NULL)
    {
        n = DocItem->nText;

        while(n > 0)
        {
            if (PtInRect(&bl->rc, pt))
            {
                return TRUE;
            }
            n -= bl->nChars + bl->nSkip;
            bl++;
        }
    }
    
    return FALSE;
}
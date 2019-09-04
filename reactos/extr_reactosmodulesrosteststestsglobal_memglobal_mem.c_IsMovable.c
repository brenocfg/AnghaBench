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
typedef  scalar_t__ LPVOID ;
typedef  scalar_t__ HGLOBAL ;

/* Variables and functions */
 scalar_t__ GlobalLock (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 

int IsMovable(HGLOBAL hMem)
{
    LPVOID pMem = 0;
    int    rc   = 0;

    pMem = GlobalLock(hMem);
    if (pMem != hMem)
    {
        rc = 1;
    }
    GlobalUnlock(hMem);

    return rc;
}
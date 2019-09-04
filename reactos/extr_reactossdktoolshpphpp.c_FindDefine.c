#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cchName; struct TYPE_4__* pNext; int /*<<< orphan*/  pszName; } ;
typedef  TYPE_1__* PDEFINE ;

/* Variables and functions */
 TYPE_1__* gpDefines ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int strxlen (char const*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

PDEFINE
FindDefine(const char *p, char **pNext)
{
    PDEFINE pDefine;
    int cchName;

    cchName = strxlen(p);
    if (pNext)
        *pNext = (char*)p + cchName;

    /* search for the define in the global list */
    pDefine = gpDefines;
    while (pDefine != 0)
    {
        trace("found a define: %s\n", pDefine->pszName);
        if (pDefine->cchName == cchName)
        {
            if (strncmp(p, pDefine->pszName, cchName) == 0)
            {
                return pDefine;
            }
        }
        pDefine = pDefine->pNext;
    }
    return 0;
}
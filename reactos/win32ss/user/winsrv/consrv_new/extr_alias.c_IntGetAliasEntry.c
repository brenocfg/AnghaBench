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
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  lpSource; } ;
struct TYPE_5__ {TYPE_2__* Data; } ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  TYPE_2__* PALIAS_ENTRY ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PALIAS_ENTRY
IntGetAliasEntry(PALIAS_HEADER Header, LPCWSTR lpSrcName)
{
    PALIAS_ENTRY RootHeader;

    if (Header == NULL) return NULL;

    RootHeader = Header->Data;
    while (RootHeader)
    {
        INT diff;
        DPRINT("IntGetAliasEntry->lpSource %S\n", RootHeader->lpSource);
        diff = _wcsicmp(RootHeader->lpSource, lpSrcName);
        if (!diff) return RootHeader;
        if (diff > 0) break;

        RootHeader = RootHeader->Next;
    }
    return NULL;
}
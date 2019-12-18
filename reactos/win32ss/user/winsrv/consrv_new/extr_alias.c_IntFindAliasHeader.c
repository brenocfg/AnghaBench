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
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  lpExeName; } ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PALIAS_HEADER
IntFindAliasHeader(PALIAS_HEADER RootHeader, LPCWSTR lpExeName)
{
    while (RootHeader)
    {
        INT diff = _wcsicmp(RootHeader->lpExeName, lpExeName);
        if (!diff) return RootHeader;
        if (diff > 0) break;

        RootHeader = RootHeader->Next;
    }
    return NULL;
}
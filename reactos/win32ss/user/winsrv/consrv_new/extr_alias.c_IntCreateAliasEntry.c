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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * Next; scalar_t__ lpTarget; scalar_t__ lpSource; } ;
typedef  TYPE_1__* PALIAS_ENTRY ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  ALIAS_ENTRY ;

/* Variables and functions */
 TYPE_1__* ConsoleAllocHeap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,scalar_t__) ; 
 int wcslen (scalar_t__) ; 

PALIAS_ENTRY
IntCreateAliasEntry(LPCWSTR lpSource, LPCWSTR lpTarget)
{
    UINT dwSource;
    UINT dwTarget;
    PALIAS_ENTRY Entry;

    dwSource = wcslen(lpSource) + 1;
    dwTarget = wcslen(lpTarget) + 1;

    Entry = ConsoleAllocHeap(0, sizeof(ALIAS_ENTRY) + sizeof(WCHAR) * (dwSource + dwTarget));
    if (!Entry) return Entry;

    Entry->lpSource = (LPCWSTR)(Entry + 1);
    wcscpy((LPWSTR)Entry->lpSource, lpSource);
    Entry->lpTarget = Entry->lpSource + dwSource;
    wcscpy((LPWSTR)Entry->lpTarget, lpTarget);
    Entry->Next = NULL;

    return Entry;
}
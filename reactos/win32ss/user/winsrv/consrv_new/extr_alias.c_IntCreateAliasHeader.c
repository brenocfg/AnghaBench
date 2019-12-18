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
struct TYPE_4__ {int /*<<< orphan*/ * Next; int /*<<< orphan*/ * Data; scalar_t__ lpExeName; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  TYPE_1__* PALIAS_HEADER ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  ALIAS_HEADER ;

/* Variables and functions */
 TYPE_1__* ConsoleAllocHeap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,scalar_t__) ; 
 int wcslen (scalar_t__) ; 

PALIAS_HEADER
IntCreateAliasHeader(LPCWSTR lpExeName)
{
    PALIAS_HEADER Entry;
    UINT dwLength = wcslen(lpExeName) + 1;

    Entry = ConsoleAllocHeap(0, sizeof(ALIAS_HEADER) + sizeof(WCHAR) * dwLength);
    if (!Entry) return Entry;

    Entry->lpExeName = (LPCWSTR)(Entry + 1);
    wcscpy((PWCHAR)Entry->lpExeName, lpExeName);
    Entry->Data = NULL;
    Entry->Next = NULL;
    return Entry;
}
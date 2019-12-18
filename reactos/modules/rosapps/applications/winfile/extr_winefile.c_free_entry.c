#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ iDesktop; int /*<<< orphan*/  iMalloc; } ;
struct TYPE_5__ {scalar_t__ hicon; scalar_t__ folder; scalar_t__ pidl; } ;
typedef  scalar_t__ HICON ;
typedef  TYPE_1__ Entry ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__ Globals ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IShellFolder_Release (scalar_t__) ; 

__attribute__((used)) static void free_entry(Entry* entry)
{
	if (entry->hicon && entry->hicon!=(HICON)-1)
		DestroyIcon(entry->hicon);

	if (entry->folder && entry->folder!=Globals.iDesktop)
		IShellFolder_Release(entry->folder);

	if (entry->pidl)
		IMalloc_Free(Globals.iMalloc, entry->pidl);

	HeapFree(GetProcessHeap(), 0, entry);
}
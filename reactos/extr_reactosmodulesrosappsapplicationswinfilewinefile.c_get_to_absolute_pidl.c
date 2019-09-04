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
struct TYPE_4__ {scalar_t__ etype; scalar_t__ pidl; struct TYPE_4__* up; } ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ Entry ;

/* Variables and functions */
 scalar_t__ ET_SHELL ; 
 scalar_t__ ET_WINDOWS ; 
 int /*<<< orphan*/ * ILClone (scalar_t__) ; 
 int /*<<< orphan*/ * ILCombine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  get_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_path_pidl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPITEMIDLIST get_to_absolute_pidl(Entry* entry, HWND hwnd)
{
	if (entry->up && entry->up->etype==ET_SHELL) {
		LPITEMIDLIST idl = NULL;

		while (entry->up) {
			idl = ILCombine(ILClone(entry->pidl), idl);
			entry = entry->up;
		}

		return idl;
	} else if (entry->etype == ET_WINDOWS) {
		WCHAR path[MAX_PATH];

		get_path(entry, path);

		return get_path_pidl(path, hwnd);
	} else if (entry->pidl)
		return ILClone(entry->pidl);

	return NULL;
}
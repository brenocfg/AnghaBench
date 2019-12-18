#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_11__ {scalar_t__ prescan_node; } ;
struct TYPE_9__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
struct TYPE_10__ {scalar_t__ etype; TYPE_1__ data; struct TYPE_10__* next; struct TYPE_10__* down; } ;
typedef  int /*<<< orphan*/  SORT_ORDER ;
typedef  scalar_t__* PWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ Entry ;

/* Variables and functions */
 scalar_t__ ET_SHELL ; 
 scalar_t__ ET_UNIX ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 TYPE_8__ Globals ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SortDirectory (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_directory_shell (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_directory_unix (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  read_directory_win (TYPE_2__*,scalar_t__*) ; 

__attribute__((used)) static void read_directory(Entry* dir, LPCWSTR path, SORT_ORDER sortOrder, HWND hwnd)
{
	WCHAR buffer[MAX_PATH];
	Entry* entry;
	LPCWSTR s;
	PWSTR d;

	if (dir->etype == ET_SHELL)
	{
		read_directory_shell(dir, hwnd);

		if (Globals.prescan_node) {
			s = path;
			d = buffer;

			while(*s)
				*d++ = *s++;

			*d++ = '\\';

			for(entry=dir->down; entry; entry=entry->next)
				if (entry->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					read_directory_shell(entry, hwnd);
					SortDirectory(entry, sortOrder);
				}
		}
	}
	else
#ifdef __WINE__
	if (dir->etype == ET_UNIX)
	{
		read_directory_unix(dir, path);

		if (Globals.prescan_node) {
			s = path;
			d = buffer;

			while(*s)
				*d++ = *s++;

			*d++ = '/';

			for(entry=dir->down; entry; entry=entry->next)
				if (entry->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					lstrcpyW(d, entry->data.cFileName);
					read_directory_unix(entry, buffer);
					SortDirectory(entry, sortOrder);
				}
		}
	}
	else
#endif
	{
		read_directory_win(dir, path);

		if (Globals.prescan_node) {
			s = path;
			d = buffer;

			while(*s)
				*d++ = *s++;

			*d++ = '\\';

			for(entry=dir->down; entry; entry=entry->next)
				if (entry->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					lstrcpyW(d, entry->data.cFileName);
					read_directory_win(entry, buffer);
					SortDirectory(entry, sortOrder);
				}
		}
	}

	SortDirectory(dir, sortOrder);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  expanded; scalar_t__ down; int /*<<< orphan*/  etype; } ;
struct TYPE_8__ {TYPE_2__ entry; } ;
typedef  int /*<<< orphan*/  SORT_ORDER ;
typedef  TYPE_1__ Root ;
typedef  char* PWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  TYPE_2__ Entry ;

/* Variables and functions */
 int /*<<< orphan*/  ET_WINDOWS ; 
 scalar_t__ IDC_WAIT ; 
 int /*<<< orphan*/  LoadCursorW (int /*<<< orphan*/ ,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* find_entry_win (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  read_directory (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Entry* read_tree_win(Root* root, LPCWSTR path, SORT_ORDER sortOrder, HWND hwnd)
{
	WCHAR buffer[MAX_PATH];
	Entry* entry = &root->entry;
	LPCWSTR s = path;
	PWSTR d = buffer;

	HCURSOR old_cursor = SetCursor(LoadCursorW(0, (LPCWSTR)IDC_WAIT));

	entry->etype = ET_WINDOWS;
	while(entry) {
		while(*s && *s != '\\' && *s != '/')
			*d++ = *s++;

		while(*s == '\\' || *s == '/')
			s++;

		*d++ = '\\';
		*d = '\0';

		read_directory(entry, buffer, sortOrder, hwnd);

		if (entry->down)
			entry->expanded = TRUE;

		if (!*s)
			break;

		entry = find_entry_win(entry, s);
	}

	SetCursor(old_cursor);

	return entry;
}
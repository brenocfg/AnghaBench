#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dwFileAttributes; char* cFileName; } ;
struct TYPE_8__ {struct TYPE_8__* down; scalar_t__ expanded; TYPE_1__ data; struct TYPE_8__* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  hwnd; scalar_t__ treePane; } ;
typedef  TYPE_2__ Pane ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ Entry ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
#define  FT_DOCUMENT 129 
#define  FT_EXECUTABLE 128 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TF_DIRECTORIES ; 
 int TF_DOCUMENTS ; 
 int TF_HIDDEN ; 
 int TF_OTHERS ; 
 int TF_PROGRAMS ; 
 int get_file_type (char*) ; 
 int /*<<< orphan*/  pattern_imatch (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_entries(Pane* pane, Entry* dir, LPCWSTR pattern, int filter_flags, int idx)
{
	Entry* entry = dir;

	if (!entry)
		return idx;

	ShowWindow(pane->hwnd, SW_HIDE);

	for(; entry; entry=entry->next) {
		if (pane->treePane && !(entry->data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
			continue;

		if (entry->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			/* don't display entries "." and ".." in the left pane */
			if (pane->treePane && entry->data.cFileName[0] == '.')
                                if (entry->data.cFileName[1] == '\0' ||
                                    (entry->data.cFileName[1] == '.' &&
                                    entry->data.cFileName[2] == '\0'))
					continue;

			/* filter directories in right pane */
			if (!pane->treePane && !(filter_flags&TF_DIRECTORIES))
				continue;
		}

		/* filter using the file name pattern */
		if (pattern)
			if (!pattern_imatch(entry->data.cFileName, pattern))
				continue;

		/* filter system and hidden files */
		if (!(filter_flags&TF_HIDDEN) && (entry->data.dwFileAttributes&(FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM)))
			continue;

		/* filter looking at the file type */
		if ((filter_flags&(TF_PROGRAMS|TF_DOCUMENTS|TF_OTHERS)) != (TF_PROGRAMS|TF_DOCUMENTS|TF_OTHERS))
			switch(get_file_type(entry->data.cFileName)) {
			  case FT_EXECUTABLE:
			  	if (!(filter_flags & TF_PROGRAMS))
					continue;
				break;

			  case FT_DOCUMENT:
				if (!(filter_flags & TF_DOCUMENTS))
					continue;
				break;

			  default: /* TF_OTHERS */
				if (!(filter_flags & TF_OTHERS))
					continue;
			}

		if (idx != -1)
			idx++;

		SendMessageW(pane->hwnd, LB_INSERTSTRING, idx, (LPARAM)entry);

		if (pane->treePane && entry->expanded)
			idx = insert_entries(pane, entry->down, pattern, filter_flags, idx);
	}

	ShowWindow(pane->hwnd, SW_SHOW);

	return idx;
}
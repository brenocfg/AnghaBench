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
struct TYPE_5__ {char* cFileName; char* cAlternateFileName; } ;
struct TYPE_6__ {TYPE_1__ data; struct TYPE_6__* next; struct TYPE_6__* down; } ;
typedef  char* LPCWSTR ;
typedef  TYPE_2__ Entry ;

/* Variables and functions */
 scalar_t__ tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Entry* find_entry_win(Entry* dir, LPCWSTR name)
{
	Entry* entry;

	for(entry=dir->down; entry; entry=entry->next) {
		LPCWSTR p = name;
		LPCWSTR q = entry->data.cFileName;

		do {
			if (!*p || *p == '\\' || *p == '/')
				return entry;
		} while(tolower(*p++) == tolower(*q++));

		p = name;
		q = entry->data.cAlternateFileName;

		do {
			if (!*p || *p == '\\' || *p == '/')
				return entry;
		} while(tolower(*p++) == tolower(*q++));
	}

	return 0;
}
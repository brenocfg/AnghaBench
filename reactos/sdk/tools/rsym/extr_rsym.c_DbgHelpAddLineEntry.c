#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct DbgHelpStringTab {int CurLineEntries; int LineEntries; struct DbgHelpLineEntry* LineEntryData; } ;
struct DbgHelpLineEntry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct DbgHelpLineEntry*,int /*<<< orphan*/ ,int) ; 
 struct DbgHelpLineEntry* realloc (struct DbgHelpLineEntry*,int) ; 

__attribute__((used)) static struct DbgHelpLineEntry*
DbgHelpAddLineEntry(struct DbgHelpStringTab *tab)
{
    if (tab->CurLineEntries == tab->LineEntries)
    {
        struct DbgHelpLineEntry *newEntries = realloc(tab->LineEntryData,
                                                      tab->LineEntries * 2 * sizeof(struct DbgHelpLineEntry));

        if (!newEntries)
            return 0;

        tab->LineEntryData = newEntries;

        memset(tab->LineEntryData + tab->LineEntries, 0, sizeof(struct DbgHelpLineEntry) * tab->LineEntries);
        tab->LineEntries *= 2;
    }

    return &tab->LineEntryData[tab->CurLineEntries++];
}
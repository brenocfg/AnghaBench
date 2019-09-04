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
struct GenericTable {scalar_t__ entries; int /*<<< orphan*/  numEntries; } ;
typedef  int /*<<< orphan*/  compareFunc ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 void* bsearch (void const*,scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT findValueInTable(const void *key,
    struct GenericTable *table, size_t tableEntrySize, compareFunc compare)
{
    UINT index = 0;
    void *value;

    value = bsearch(key, table->entries, table->numEntries, tableEntrySize,
        compare);
    if (value)
        index = ((BYTE *)value - (BYTE *)table->entries) / tableEntrySize + 1;
    return index;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  urlcache_header ;
struct hash_entry {scalar_t__ key; } ;
struct TYPE_3__ {struct hash_entry* hash_table; } ;
typedef  TYPE_1__ entry_hash_table ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HASHTABLE_DEL ; 
 scalar_t__ HASHTABLE_FREE ; 
 size_t HASHTABLE_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL urlcache_enum_hash_table_entries(const urlcache_header *pHeader, const entry_hash_table *pHashEntry,
                                          DWORD * index, const struct hash_entry **ppHashEntry)
{
    for (; *index < HASHTABLE_SIZE ; (*index)++)
    {
        if (pHashEntry->hash_table[*index].key==HASHTABLE_FREE || pHashEntry->hash_table[*index].key==HASHTABLE_DEL)
            continue;

        *ppHashEntry = &pHashEntry->hash_table[*index];
        TRACE("entry found %d\n", *index);
        return TRUE;
    }
    TRACE("no more entries (%d)\n", *index);
    return FALSE;
}
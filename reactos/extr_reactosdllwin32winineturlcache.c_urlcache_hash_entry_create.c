#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  hash_table_off; } ;
typedef  TYPE_2__ urlcache_header ;
struct hash_entry {int key; int offset; } ;
struct TYPE_10__ {scalar_t__ signature; } ;
struct TYPE_12__ {scalar_t__ id; struct hash_entry* hash_table; TYPE_1__ header; int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ entry_hash_table ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 int ERROR_SUCCESS ; 
 int HASHTABLE_BLOCKSIZE ; 
 int HASHTABLE_DEL ; 
 int HASHTABLE_FLAG_BITS ; 
 int HASHTABLE_FREE ; 
 int HASHTABLE_NUM_ENTRIES ; 
 scalar_t__ HASH_SIGNATURE ; 
 int urlcache_create_hash_table (TYPE_2__*,TYPE_3__*,TYPE_3__**) ; 
 TYPE_3__* urlcache_get_hash_table (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int urlcache_hash_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD urlcache_hash_entry_create(urlcache_header *pHeader, LPCSTR lpszUrl, DWORD dwOffsetEntry, DWORD dwFieldType)
{
    /* see urlcache_find_hash_entry for structure of hash tables */

    DWORD key = urlcache_hash_key(lpszUrl);
    DWORD offset = (key & (HASHTABLE_NUM_ENTRIES-1)) * HASHTABLE_BLOCKSIZE;
    entry_hash_table* pHashEntry, *pHashPrev = NULL;
    DWORD id = 0;
    DWORD error;

    key = ((key >> HASHTABLE_FLAG_BITS) << HASHTABLE_FLAG_BITS) + dwFieldType;

    for (pHashEntry = urlcache_get_hash_table(pHeader, pHeader->hash_table_off);
         pHashEntry; pHashEntry = urlcache_get_hash_table(pHeader, pHashEntry->next))
    {
        int i;
        pHashPrev = pHashEntry;

        if (pHashEntry->id != id++)
        {
            ERR("not right hash table number (%d) expected %d\n", pHashEntry->id, id);
            break;
        }
        /* make sure that it is in fact a hash entry */
        if (pHashEntry->header.signature != HASH_SIGNATURE)
        {
            ERR("not right signature (\"%.4s\") - expected \"HASH\"\n", (LPCSTR)&pHashEntry->header.signature);
            break;
        }

        for (i = 0; i < HASHTABLE_BLOCKSIZE; i++)
        {
            struct hash_entry *pHashElement = &pHashEntry->hash_table[offset + i];
            if (pHashElement->key==HASHTABLE_FREE || pHashElement->key==HASHTABLE_DEL) /* if the slot is free */
            {
                pHashElement->key = key;
                pHashElement->offset = dwOffsetEntry;
                return ERROR_SUCCESS;
            }
        }
    }
    error = urlcache_create_hash_table(pHeader, pHashPrev, &pHashEntry);
    if (error != ERROR_SUCCESS)
        return error;

    pHashEntry->hash_table[offset].key = key;
    pHashEntry->hash_table[offset].offset = dwOffsetEntry;
    return ERROR_SUCCESS;
}
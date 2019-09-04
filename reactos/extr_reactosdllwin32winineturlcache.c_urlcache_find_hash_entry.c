#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hash_table_off; } ;
typedef  TYPE_2__ urlcache_header ;
struct hash_entry {int key; } ;
struct TYPE_7__ {scalar_t__ signature; } ;
struct TYPE_9__ {scalar_t__ id; struct hash_entry* hash_table; TYPE_1__ header; int /*<<< orphan*/  next; } ;
typedef  TYPE_3__ entry_hash_table ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int HASHTABLE_BLOCKSIZE ; 
 int HASHTABLE_FLAG_BITS ; 
 int HASHTABLE_NUM_ENTRIES ; 
 scalar_t__ HASH_SIGNATURE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* urlcache_get_hash_table (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int urlcache_hash_key (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL urlcache_find_hash_entry(const urlcache_header *pHeader, LPCSTR lpszUrl, struct hash_entry **ppHashEntry)
{
    /* structure of hash table:
     *  448 entries divided into 64 blocks
     *  each block therefore contains a chain of 7 key/offset pairs
     * how position in table is calculated:
     *  1. the url is hashed in helper function
     *  2. the key % HASHTABLE_NUM_ENTRIES is the bucket number
     *  3. bucket number * HASHTABLE_BLOCKSIZE is offset of the bucket
     *
     * note:
     *  there can be multiple hash tables in the file and the offset to
     *  the next one is stored in the header of the hash table
     */
    DWORD key = urlcache_hash_key(lpszUrl);
    DWORD offset = (key & (HASHTABLE_NUM_ENTRIES-1)) * HASHTABLE_BLOCKSIZE;
    entry_hash_table* pHashEntry;
    DWORD id = 0;

    key >>= HASHTABLE_FLAG_BITS;

    for (pHashEntry = urlcache_get_hash_table(pHeader, pHeader->hash_table_off);
         pHashEntry; pHashEntry = urlcache_get_hash_table(pHeader, pHashEntry->next))
    {
        int i;
        if (pHashEntry->id != id++)
        {
            ERR("Error: not right hash table number (%d) expected %d\n", pHashEntry->id, id);
            continue;
        }
        /* make sure that it is in fact a hash entry */
        if (pHashEntry->header.signature != HASH_SIGNATURE)
        {
            ERR("Error: not right signature (\"%.4s\") - expected \"HASH\"\n", (LPCSTR)&pHashEntry->header.signature);
            continue;
        }

        for (i = 0; i < HASHTABLE_BLOCKSIZE; i++)
        {
            struct hash_entry *pHashElement = &pHashEntry->hash_table[offset + i];
            if (key == pHashElement->key>>HASHTABLE_FLAG_BITS)
            {
                /* FIXME: we should make sure that this is the right element
                 * before returning and claiming that it is. We can do this
                 * by doing a simple compare between the URL we were given
                 * and the URL stored in the entry. However, this assumes
                 * we know the format of all the entries stored in the
                 * hash table */
                *ppHashEntry = pHashElement;
                return TRUE;
            }
        }
    }
    return FALSE;
}
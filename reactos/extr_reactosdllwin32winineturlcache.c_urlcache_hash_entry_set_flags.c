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
struct hash_entry {int key; } ;
typedef  int DWORD ;

/* Variables and functions */
 int HASHTABLE_FLAG_BITS ; 

__attribute__((used)) static void urlcache_hash_entry_set_flags(struct hash_entry *pHashEntry, DWORD dwFlag)
{
    pHashEntry->key = (pHashEntry->key >> HASHTABLE_FLAG_BITS << HASHTABLE_FLAG_BITS) | dwFlag;
}
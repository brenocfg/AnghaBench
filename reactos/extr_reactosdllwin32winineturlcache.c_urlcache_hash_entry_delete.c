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
struct hash_entry {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HASHTABLE_DEL ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL urlcache_hash_entry_delete(struct hash_entry *pHashEntry)
{
    pHashEntry->key = HASHTABLE_DEL;
    return TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint64_t ;
struct TYPE_10__ {void const* key; struct TYPE_10__* next; } ;
typedef  TYPE_2__ dictEntry ;
struct TYPE_11__ {TYPE_1__* ht; } ;
typedef  TYPE_3__ dict ;
struct TYPE_9__ {unsigned long sizemask; TYPE_2__** table; } ;

/* Variables and functions */
 scalar_t__ DICT_ERR ; 
 scalar_t__ _dictExpandIfNeeded (TYPE_3__*) ; 
 scalar_t__ dictCompareKeys (TYPE_3__*,void const*,void const*) ; 
 int /*<<< orphan*/  dictIsRehashing (TYPE_3__*) ; 

__attribute__((used)) static long _dictKeyIndex(dict *d, const void *key, uint64_t hash, dictEntry **existing)
{
    unsigned long idx, table;
    dictEntry *he;
    if (existing) *existing = NULL;

    /* Expand the hash table if needed */
    if (_dictExpandIfNeeded(d) == DICT_ERR)
        return -1;
    for (table = 0; table <= 1; table++) {
        idx = hash & d->ht[table].sizemask;
        /* Search if this slot does not already contain the given key */
        he = d->ht[table].table[idx];
        while(he) {
            if (key==he->key || dictCompareKeys(d, key, he->key)) {
                if (existing) *existing = he;
                return -1;
            }
            he = he->next;
        }
        if (!dictIsRehashing(d)) break;
    }
    return idx;
}
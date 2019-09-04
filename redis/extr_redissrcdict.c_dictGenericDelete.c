#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_16__ {void const* key; struct TYPE_16__* next; } ;
typedef  TYPE_2__ dictEntry ;
struct TYPE_17__ {TYPE_1__* ht; } ;
typedef  TYPE_3__ dict ;
struct TYPE_15__ {scalar_t__ used; size_t sizemask; TYPE_2__** table; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dictRehashStep (TYPE_3__*) ; 
 scalar_t__ dictCompareKeys (TYPE_3__*,void const*,void const*) ; 
 int /*<<< orphan*/  dictFreeKey (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dictFreeVal (TYPE_3__*,TYPE_2__*) ; 
 size_t dictHashKey (TYPE_3__*,void const*) ; 
 scalar_t__ dictIsRehashing (TYPE_3__*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

__attribute__((used)) static dictEntry *dictGenericDelete(dict *d, const void *key, int nofree) {
    uint64_t h, idx;
    dictEntry *he, *prevHe;
    int table;

    if (d->ht[0].used == 0 && d->ht[1].used == 0) return NULL;

    if (dictIsRehashing(d)) _dictRehashStep(d);
    h = dictHashKey(d, key);

    for (table = 0; table <= 1; table++) {
        idx = h & d->ht[table].sizemask;
        he = d->ht[table].table[idx];
        prevHe = NULL;
        while(he) {
            if (key==he->key || dictCompareKeys(d, key, he->key)) {
                /* Unlink the element from the list */
                if (prevHe)
                    prevHe->next = he->next;
                else
                    d->ht[table].table[idx] = he->next;
                if (!nofree) {
                    dictFreeKey(d, he);
                    dictFreeVal(d, he);
                    zfree(he);
                }
                d->ht[table].used--;
                return he;
            }
            prevHe = he;
            he = he->next;
        }
        if (!dictIsRehashing(d)) break;
    }
    return NULL; /* not found */
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ dictEntry ;
struct TYPE_8__ {scalar_t__ size; unsigned int sizemask; TYPE_1__** table; } ;
typedef  TYPE_2__ dict ;

/* Variables and functions */
 scalar_t__ dictCompareHashKeys (TYPE_2__*,void const*,int /*<<< orphan*/ ) ; 
 unsigned int dictHashKey (TYPE_2__*,void const*) ; 

__attribute__((used)) static dictEntry *dictFind(dict *ht, const void *key) {
    dictEntry *he;
    unsigned int h;

    if (ht->size == 0) return NULL;
    h = dictHashKey(ht, key) & ht->sizemask;
    he = ht->table[h];
    while(he) {
        if (dictCompareHashKeys(ht, key, he->key))
            return he;
        he = he->next;
    }
    return NULL;
}
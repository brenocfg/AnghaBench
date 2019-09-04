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
struct dictionary_entry {struct dictionary_entry* next; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
struct dictionary {int /*<<< orphan*/  num_entries; int /*<<< orphan*/  extra; int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dictionary_entry*) ; 
 int /*<<< orphan*/  TRACE (char*,struct dictionary*,void const*) ; 
 struct dictionary_entry** dictionary_find_internal (struct dictionary*,void const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dictionary_remove(struct dictionary *d, const void *k)
{
    struct dictionary_entry **prior, *temp;

    TRACE("(%p, %p)\n", d, k);
    if (!d)
        return;
    if ((prior = dictionary_find_internal(d, k)))
    {
        temp = *prior;
        if (d->destroy)
            d->destroy((*prior)->key, (*prior)->value, d->extra);
        *prior = (*prior)->next;
        HeapFree(GetProcessHeap(), 0, temp);
        d->num_entries--;
    }
}
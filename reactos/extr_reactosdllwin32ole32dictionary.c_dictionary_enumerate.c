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
struct dictionary_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct dictionary_entry* next; } ;
struct dictionary {int /*<<< orphan*/  extra; struct dictionary_entry* head; } ;
typedef  int /*<<< orphan*/  (* enumeratefunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct dictionary*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*),void*) ; 

void dictionary_enumerate(struct dictionary *d, enumeratefunc e, void *closure)
{
    struct dictionary_entry *p;

    TRACE("(%p, %p, %p)\n", d, e, closure);
    if (!d)
        return;
    if (!e)
        return;
    for (p = d->head; p; p = p->next)
        if (!e(p->key, p->value, d->extra, closure))
            break;
}
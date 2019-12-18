#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int sizearray; int /*<<< orphan*/ * array; int /*<<< orphan*/ * metatable; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  (* ObjectRelationshipReport ) (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * gcvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnodelast (TYPE_1__*) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ *) ; 
 unsigned int nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttistable (int /*<<< orphan*/  const*) ; 
 unsigned int ttnov (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void report_table(Table *h, ObjectRelationshipReport cb)
{
	Node *n, *limit = gnodelast(h);
    unsigned int i;
	
	if (h->metatable != NULL)
	{
		cb(h, h->metatable, 4, NULL, 0, NULL);
	}
	
    for (i = 0; i < h->sizearray; i++)
	{
		const TValue *item = &h->array[i];
		if (ttistable(item))
		{
		    cb(h, gcvalue(item), 2, NULL, i + 1, NULL);
		}
	}

    for (n = gnode(h, 0); n < limit; n++)
	{
        if (!ttisnil(gval(n)))
        {
            const TValue *key = gkey(n);
			if (ttistable(key))
			{
				cb(h, gcvalue(key), 3, NULL, 0, NULL);
			}
            const TValue *value = gval(n);
			if (ttistable(value))
			{
				if (ttisstring(key))
				{
					cb(h, gcvalue(value), 1, getstr(tsvalue(key)), 0, NULL);
				}
				else if(ttisnumber(key))
				{
					cb(h, gcvalue(value), 2, NULL, nvalue(key), NULL);
				}
				else
				{
					// ???
					cb(h, gcvalue(value), 1, NULL, ttnov(key), NULL);
				}
			}
		}
    }
}
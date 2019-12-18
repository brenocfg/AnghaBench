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
struct TYPE_7__ {scalar_t__ sizearray; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * gnode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnodelast (TYPE_1__*) ; 
 int /*<<< orphan*/  gval (int /*<<< orphan*/ *) ; 
 scalar_t__ luaH_getn (TYPE_1__*) ; 
 scalar_t__ sizenode (TYPE_1__*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int table_size (Table *h, int fast)
{
	if (fast)
	{
		return (int)sizenode(h) + (int)h->sizearray;
	}
	else
	{
		Node *n, *limit = gnodelast(h);
		int i = (int)luaH_getn(h);
		for (n = gnode(h, 0); n < limit; n++)
		{ 
			if (!ttisnil(gval(n)))
			{
				i++;
			}
		}
		return i;
	}
}
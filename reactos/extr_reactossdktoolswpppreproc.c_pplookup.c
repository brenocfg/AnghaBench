#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ident; struct TYPE_4__* next; } ;
typedef  TYPE_1__ pp_entry_t ;
struct TYPE_5__ {TYPE_1__** defines; } ;

/* Variables and functions */
 TYPE_3__* pp_def_state ; 
 int pphash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

pp_entry_t *pplookup(const char *ident)
{
	int idx;
	pp_entry_t *ppp;

	if(!ident)
		return NULL;
	idx = pphash(ident);
	for(ppp = pp_def_state->defines[idx]; ppp; ppp = ppp->next)
	{
		if(!strcmp(ident, ppp->ident))
			return ppp;
	}
	return NULL;
}
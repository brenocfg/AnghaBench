#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  text; } ;
struct TYPE_7__ {int /*<<< orphan*/  filename; TYPE_1__ subst; int /*<<< orphan*/  ident; } ;
typedef  TYPE_2__ pp_entry_t ;
struct TYPE_8__ {char* input; int line_number; scalar_t__ debug; scalar_t__ pedantic; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pp_entry (TYPE_2__*,int) ; 
 TYPE_4__ pp_status ; 
 int pphash (char const*) ; 
 TYPE_2__* pplookup (char const*) ; 
 int /*<<< orphan*/  ppy_warning (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,char const*) ; 

void pp_del_define(const char *name)
{
	pp_entry_t *ppp;
	int idx = pphash(name);

	if((ppp = pplookup(name)) == NULL)
	{
		if(pp_status.pedantic)
			ppy_warning("%s was not defined", name);
		return;
	}

	if(pp_status.debug)
		printf("Deleting (%s, %d) <%s>\n", pp_status.input, pp_status.line_number, name);

	free( ppp->ident );
	free( ppp->subst.text );
	free( ppp->filename );
	free_pp_entry( ppp, idx );
}
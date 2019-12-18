#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ident; } ;
typedef  TYPE_1__ pp_entry_t ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__** defines; } ;
typedef  TYPE_2__ pp_def_state_t ;

/* Variables and functions */
 int HASHKEY ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* pp_def_state ; 
 int /*<<< orphan*/  pp_del_define (int /*<<< orphan*/ ) ; 

void pp_pop_define_state(void)
{
    int i;
    pp_entry_t *ppp;
    pp_def_state_t *state;

    for (i = 0; i < HASHKEY; i++)
    {
        while ((ppp = pp_def_state->defines[i]) != NULL) pp_del_define( ppp->ident );
    }
    state = pp_def_state;
    pp_def_state = state->next;
    free( state );
}
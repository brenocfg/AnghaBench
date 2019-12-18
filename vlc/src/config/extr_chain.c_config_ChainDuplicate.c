#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* p_next; int /*<<< orphan*/ * psz_value; int /*<<< orphan*/ * psz_name; } ;
typedef  TYPE_1__ config_chain_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

config_chain_t *config_ChainDuplicate( const config_chain_t *p_src )
{
    config_chain_t *p_dst = NULL;
    config_chain_t **pp_last = &p_dst;

    for( ; p_src != NULL; p_src = p_src->p_next )
    {
        config_chain_t *p = malloc( sizeof(*p) );
        if( !p )
            break;
        p->p_next    = NULL;
        p->psz_name  = p_src->psz_name  ? strdup( p_src->psz_name )  : NULL;
        p->psz_value = p_src->psz_value ? strdup( p_src->psz_value ) : NULL;

        *pp_last = p;
        pp_last = &p->p_next;
    }
    return p_dst;
}
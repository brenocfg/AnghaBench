#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  psz_value; int /*<<< orphan*/  psz_name; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void config_ChainDestroy( config_chain_t *p_cfg )
{
    while( p_cfg != NULL )
    {
        config_chain_t *p_next;

        p_next = p_cfg->p_next;

        FREENULL( p_cfg->psz_name );
        FREENULL( p_cfg->psz_value );
        free( p_cfg );

        p_cfg = p_next;
    }
}
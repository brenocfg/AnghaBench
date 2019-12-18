#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int fdc; int* fdv; int /*<<< orphan*/  interrupt; } ;
typedef  TYPE_1__ vlclua_dtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int /*<<< orphan*/  vlc_interrupt_destroy (int /*<<< orphan*/ ) ; 

void vlclua_fd_cleanup( vlclua_dtable_t *dt )
{
    for( unsigned i = 0; i < dt->fdc; i++ )
        if( dt->fdv[i] != -1 )
            net_Close( dt->fdv[i] );
    free( dt->fdv );
    vlc_interrupt_destroy(dt->interrupt);
}
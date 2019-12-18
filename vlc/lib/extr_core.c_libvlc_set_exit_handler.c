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
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_SetExitHandler (int /*<<< orphan*/ *,void (*) (void*),void*) ; 

void libvlc_set_exit_handler( libvlc_instance_t *p_i, void (*cb) (void *),
                              void *data )
{
    libvlc_int_t *p_libvlc = p_i->p_libvlc_int;
    libvlc_SetExitHandler( p_libvlc, cb, data );
}
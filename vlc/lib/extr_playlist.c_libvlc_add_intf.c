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
struct TYPE_3__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 scalar_t__ libvlc_InternalAddIntf (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*,...) ; 

int libvlc_add_intf( libvlc_instance_t *p_instance, const char *name )
{
    if( libvlc_InternalAddIntf( p_instance->p_libvlc_int, name ))
    {
        if( name != NULL )
            libvlc_printerr("interface \"%s\" initialization failed", name );
        else
            libvlc_printerr("default interface initialization failed");
        return -1;
    }
    return 0;
}
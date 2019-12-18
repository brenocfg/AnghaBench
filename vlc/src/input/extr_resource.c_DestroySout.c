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
struct TYPE_3__ {int /*<<< orphan*/ * p_sout; } ;
typedef  TYPE_1__ input_resource_t ;

/* Variables and functions */
 int /*<<< orphan*/  sout_DeleteInstance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DestroySout( input_resource_t *p_resource )
{
#ifdef ENABLE_SOUT
    if( p_resource->p_sout )
        sout_DeleteInstance( p_resource->p_sout );
#endif
    p_resource->p_sout = NULL;
}
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
struct TYPE_3__ {struct TYPE_3__* psz_name; void* p_next; } ;
typedef  TYPE_1__ vlc_family_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void FreeFamilies( void *p_families, void *p_obj )
{
    vlc_family_t *p_family = ( vlc_family_t * ) p_families;

    if( p_family->p_next )
        FreeFamilies( p_family->p_next, p_obj );

    free( p_family->psz_name );
    free( p_family );
}
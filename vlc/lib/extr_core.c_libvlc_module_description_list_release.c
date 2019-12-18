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
struct TYPE_4__ {struct TYPE_4__* p_next; struct TYPE_4__* psz_help; struct TYPE_4__* psz_longname; struct TYPE_4__* psz_shortname; struct TYPE_4__* psz_name; } ;
typedef  TYPE_1__ libvlc_module_description_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void libvlc_module_description_list_release( libvlc_module_description_t *p_list )
{
    libvlc_module_description_t *p_actual, *p_before;
    p_actual = p_list;

    while ( p_actual )
    {
        free( p_actual->psz_name );
        free( p_actual->psz_shortname );
        free( p_actual->psz_longname );
        free( p_actual->psz_help );
        p_before = p_actual;
        p_actual = p_before->p_next;
        free( p_before );
    }
}
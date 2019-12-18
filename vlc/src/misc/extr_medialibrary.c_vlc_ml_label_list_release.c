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
struct TYPE_6__ {size_t i_nb_items; TYPE_1__* p_items; } ;
typedef  TYPE_2__ vlc_ml_label_list_t ;
struct TYPE_5__ {TYPE_2__* psz_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void vlc_ml_label_list_release( vlc_ml_label_list_t* p_list )
{
    if ( p_list == NULL )
        return;
    for ( size_t i = 0; i < p_list->i_nb_items; ++i )
        free( p_list->p_items[i].psz_name );
    free( p_list );
}
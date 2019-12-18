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
struct TYPE_4__ {size_t i_nb_items; int /*<<< orphan*/ * p_items; } ;
typedef  TYPE_1__ vlc_ml_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_ml_media_release_inner (int /*<<< orphan*/ *) ; 

void vlc_ml_media_list_release( vlc_ml_media_list_t* p_list )
{
    if ( p_list == NULL )
        return;
    for ( size_t i = 0; i < p_list->i_nb_items; ++i )
        vlc_ml_media_release_inner( &p_list->p_items[i] );
    free( p_list );
}
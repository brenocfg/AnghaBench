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
struct TYPE_4__ {struct TYPE_4__* psz_name; } ;
typedef  TYPE_1__ vlc_ml_genre_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void vlc_ml_genre_release( vlc_ml_genre_t* p_genre )
{
    if ( p_genre == NULL )
        return;
    free( p_genre->psz_name );
    free( p_genre );
}
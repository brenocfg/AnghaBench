#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_ml_album_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_ml_album_release_inner (int /*<<< orphan*/ *) ; 

void vlc_ml_album_release( vlc_ml_album_t* p_album )
{
    if ( p_album == NULL )
        return;
    vlc_ml_album_release_inner( p_album );
    free( p_album );
}
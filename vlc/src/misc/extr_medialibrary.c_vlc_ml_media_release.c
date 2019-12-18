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
typedef  int /*<<< orphan*/  vlc_ml_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_ml_media_release_inner (int /*<<< orphan*/ *) ; 

void vlc_ml_media_release( vlc_ml_media_t* p_media )
{
    if ( p_media == NULL )
        return;
    vlc_ml_media_release_inner( p_media );
    free( p_media );
}
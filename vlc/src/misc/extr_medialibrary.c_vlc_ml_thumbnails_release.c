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
struct TYPE_3__ {int /*<<< orphan*/  psz_mrl; } ;
typedef  TYPE_1__ vlc_ml_thumbnail_t ;

/* Variables and functions */
 int VLC_ML_THUMBNAIL_SIZE_COUNT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_ml_thumbnails_release( vlc_ml_thumbnail_t *p_thumbnails )
{
    for ( int i = 0; i < VLC_ML_THUMBNAIL_SIZE_COUNT; ++i )
        free( p_thumbnails[i].psz_mrl );
}
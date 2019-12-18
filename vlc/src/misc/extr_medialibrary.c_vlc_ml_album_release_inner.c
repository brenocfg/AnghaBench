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
struct TYPE_3__ {int /*<<< orphan*/  psz_title; int /*<<< orphan*/  psz_summary; int /*<<< orphan*/  psz_artist; int /*<<< orphan*/  thumbnails; } ;
typedef  TYPE_1__ vlc_ml_album_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ml_thumbnails_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_ml_album_release_inner( vlc_ml_album_t* p_album )
{
    vlc_ml_thumbnails_release( p_album->thumbnails );
    free( p_album->psz_artist );
    free( p_album->psz_summary );
    free( p_album->psz_title );
}
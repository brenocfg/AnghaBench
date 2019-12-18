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
struct TYPE_3__ {int /*<<< orphan*/  psz_tvdb_id; int /*<<< orphan*/  psz_summary; int /*<<< orphan*/  psz_name; int /*<<< orphan*/  psz_artwork_mrl; } ;
typedef  TYPE_1__ vlc_ml_show_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_ml_show_release_inner( vlc_ml_show_t* p_show )
{
    free( p_show->psz_artwork_mrl );
    free( p_show->psz_name );
    free( p_show->psz_summary );
    free( p_show->psz_tvdb_id );
}
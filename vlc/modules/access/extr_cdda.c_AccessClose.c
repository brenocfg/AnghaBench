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
typedef  int /*<<< orphan*/  vlc_meta_t ;
struct TYPE_3__ {int cdtextc; int /*<<< orphan*/  p_toc; scalar_t__ mbrecord; int /*<<< orphan*/ * cddb; int /*<<< orphan*/ ** cdtextv; } ;
typedef  TYPE_1__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  cddb_disc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  musicbrainz_recording_release (scalar_t__) ; 
 int /*<<< orphan*/  vcddev_toc_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AccessClose(access_sys_t *sys)
{
    for (int i = 0; i < sys->cdtextc; i++)
    {
        vlc_meta_t *meta = sys->cdtextv[i];
        if (meta != NULL)
            vlc_meta_Delete(meta);
    }
    free(sys->cdtextv);

#ifdef HAVE_LIBCDDB
    if (sys->cddb != NULL)
        cddb_disc_destroy(sys->cddb);
#endif
    if(sys->mbrecord)
        musicbrainz_recording_release(sys->mbrecord);
    vcddev_toc_Free(sys->p_toc);
}
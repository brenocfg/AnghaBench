#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yearbuf ;
typedef  int /*<<< orphan*/  vlc_meta_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  cddb_track_t ;
struct TYPE_7__ {scalar_t__ cdtextc; int /*<<< orphan*/ * cddb; TYPE_1__* p_toc; int /*<<< orphan*/ ** cdtextv; } ;
typedef  TYPE_3__ access_sys_t ;
struct TYPE_5__ {int i_tracks; } ;

/* Variables and functions */
 scalar_t__ NONEMPTY (char const*) ; 
 char* cddb_disc_get_artist (int /*<<< orphan*/ *) ; 
 char* cddb_disc_get_genre (int /*<<< orphan*/ *) ; 
 char* cddb_disc_get_title (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cddb_disc_get_track (int /*<<< orphan*/ *,int) ; 
 unsigned int cddb_disc_get_year (int /*<<< orphan*/ *) ; 
 char* cddb_track_get_artist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int const) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  vlc_meta_Merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_meta_SetDate (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_meta_SetGenre (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_SetTitle (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void AccessGetMeta(stream_t *access, vlc_meta_t *meta)
{
    access_sys_t *sys = access->p_sys;

    vlc_meta_SetTitle(meta, "Audio CD");

    /* Retrieve CD-TEXT information */
    if (sys->cdtextc > 0 && sys->cdtextv[0] != NULL)
        vlc_meta_Merge(meta, sys->cdtextv[0]);

/* Return true if the given string is not NULL and not empty */
#define NONEMPTY( psz ) ( (psz) && *(psz) )
/* If the given string is NULL or empty, fill it by the return value of 'code' */
#define ON_EMPTY( psz, code ) do { if( !NONEMPTY( psz) ) { (psz) = code; } } while(0)

    /* Retrieve CDDB information (preferred over CD-TEXT) */
#ifdef HAVE_LIBCDDB
    if (sys->cddb != NULL)
    {
        const char *str = cddb_disc_get_title(sys->cddb);
        if (NONEMPTY(str))
            vlc_meta_SetTitle(meta, str);

        str = cddb_disc_get_genre(sys->cddb);
        if (NONEMPTY(str))
            vlc_meta_SetGenre(meta, str);

        const unsigned year = cddb_disc_get_year(sys->cddb);
        if (year != 0)
        {
            char yearbuf[5];

            snprintf(yearbuf, sizeof (yearbuf), "%u", year);
            vlc_meta_SetDate(meta, yearbuf);
        }

        /* Set artist only if identical across tracks */
        str = cddb_disc_get_artist(sys->cddb);
        if (NONEMPTY(str))
        {
            for (int i = 0; i < sys->p_toc->i_tracks; i++)
            {
                cddb_track_t *t = cddb_disc_get_track(sys->cddb, i);
                if (t == NULL)
                    continue;

                const char *track_artist = cddb_track_get_artist(t);
                if (NONEMPTY(track_artist))
                {
                    if (str == NULL)
                        str = track_artist;
                    else
                    if (strcmp(str, track_artist))
                    {
                        str = NULL;
                        break;
                    }
                }
            }
        }
    }
#endif
}
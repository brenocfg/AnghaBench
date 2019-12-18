#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int i_tracks; TYPE_1__* p_sectors; } ;
typedef  TYPE_2__ vcddev_toc_t ;
struct vlc_memstream {char* ptr; } ;
typedef  int /*<<< orphan*/  musicbrainz_recording_t ;
struct TYPE_10__ {char* psz_mb_server; int /*<<< orphan*/ * psz_coverart_server; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_3__ musicbrainz_config_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_lba; } ;

/* Variables and functions */
 char* BuildMusicbrainzDiscID (TYPE_2__ const*,int,int,int) ; 
 int CD_ROM_XA_INTERVAL ; 
 int LBAPregap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * musicbrainz_lookup_recording_by_discid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * musicbrainz_lookup_recording_by_toc (TYPE_3__*,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_flush (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,int,...) ; 

__attribute__((used)) static musicbrainz_recording_t * GetMusicbrainzInfo( vlc_object_t *obj,
                                                     const vcddev_toc_t *p_toc,
                                                     int i_total, int i_first, int i_last )
{
    musicbrainz_recording_t *recording = NULL;

    char *psz_mbserver = var_InheritString( obj, "musicbrainz-server" );
    if( !psz_mbserver || !*psz_mbserver )
        return NULL;

    musicbrainz_config_t cfg = { .obj = obj,
                                 .psz_mb_server = psz_mbserver,
                                 .psz_coverart_server = NULL };

    /* Build DISC ID based on SHA1 */
    char *psz_disc_id = BuildMusicbrainzDiscID( p_toc,
                                                i_total, i_first, i_last );
    if( psz_disc_id )
    {
        recording = musicbrainz_lookup_recording_by_discid( &cfg, psz_disc_id );
    }
    else /* Fuzzy lookup using TOC */
    {
        struct vlc_memstream ms;
        if( vlc_memstream_open(&ms) )
        {
            free( psz_mbserver );
            return NULL;
        }

        vlc_memstream_printf(&ms, "toc=%u+%u", i_first, i_last );
        /* LEAD OUT sector info
         * https://github.com/metabrainz/libdiscid/blob/e46249415eb6d657ecc63667b03d670a4347712f/src/toc.c#L90 */
        int i_last_track_end;
        if (p_toc->i_tracks > i_total)
            i_last_track_end = LBAPregap(p_toc->p_sectors[i_total].i_lba) - CD_ROM_XA_INTERVAL;
        else
            i_last_track_end = LBAPregap(p_toc->p_sectors[p_toc->i_tracks].i_lba);
        vlc_memstream_printf(&ms, "+%u", i_last_track_end );
        for( int i = 0; i<i_total; i++ ) /* skipped LEAD OUT, audio only */
            vlc_memstream_printf(&ms, "+%u", LBAPregap(p_toc->p_sectors[i].i_lba) );
        if( vlc_memstream_flush(&ms) )
        {
            if( vlc_memstream_close(&ms) )
                free( ms.ptr );
            free( psz_mbserver );
            return NULL;
        }

        recording = musicbrainz_lookup_recording_by_toc( &cfg, ms.ptr );

        if( vlc_memstream_close(&ms) == 0 )
            free( ms.ptr );
    }

    free( psz_mbserver );
    return recording;
}
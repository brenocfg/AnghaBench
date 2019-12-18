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
struct TYPE_6__ {int /*<<< orphan*/  psz_imdb_id; int /*<<< orphan*/  psz_summary; } ;
struct TYPE_5__ {int /*<<< orphan*/  psz_tvdb_id; int /*<<< orphan*/  psz_summary; } ;
struct TYPE_7__ {int i_subtype; TYPE_2__ movie; TYPE_1__ show_episode; int /*<<< orphan*/  thumbnails; int /*<<< orphan*/  psz_title; int /*<<< orphan*/  p_tracks; int /*<<< orphan*/  p_files; } ;
typedef  TYPE_3__ vlc_ml_media_t ;

/* Variables and functions */
#define  VLC_ML_MEDIA_SUBTYPE_ALBUMTRACK 130 
#define  VLC_ML_MEDIA_SUBTYPE_MOVIE 129 
#define  VLC_ML_MEDIA_SUBTYPE_SHOW_EPISODE 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ml_file_list_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ml_media_release_tracks_inner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ml_thumbnails_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_ml_media_release_inner( vlc_ml_media_t* p_media )
{
    vlc_ml_file_list_release( p_media->p_files );
    vlc_ml_media_release_tracks_inner( p_media->p_tracks );
    free( p_media->psz_title );
    vlc_ml_thumbnails_release( p_media->thumbnails );
    switch( p_media->i_subtype )
    {
        case VLC_ML_MEDIA_SUBTYPE_ALBUMTRACK:
            break;
        case VLC_ML_MEDIA_SUBTYPE_SHOW_EPISODE:
            free( p_media->show_episode.psz_summary );
            free( p_media->show_episode.psz_tvdb_id );
            break;
        case VLC_ML_MEDIA_SUBTYPE_MOVIE:
            free( p_media->movie.psz_summary );
            free( p_media->movie.psz_imdb_id );
            break;
        default:
            break;
    }
}
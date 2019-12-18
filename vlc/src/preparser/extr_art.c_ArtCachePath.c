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
struct TYPE_3__ {char* psz_name; int /*<<< orphan*/  lock; scalar_t__ p_meta; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 char* ArtCacheGetDirPath (char const*,char const*,char const*,char const*,char const*) ; 
 scalar_t__ EMPTY_STR (char const*) ; 
 int /*<<< orphan*/  vlc_meta_Album ; 
 int /*<<< orphan*/  vlc_meta_Artist ; 
 int /*<<< orphan*/  vlc_meta_ArtworkURL ; 
 int /*<<< orphan*/  vlc_meta_Date ; 
 char* vlc_meta_Get (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_meta_Title ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *ArtCachePath( input_item_t *p_item )
{
    char* psz_path = NULL;
    const char *psz_artist;
    const char *psz_album;
    const char *psz_arturl;
    const char *psz_title;
    const char *psz_date;

    vlc_mutex_lock( &p_item->lock );

    if( !p_item->p_meta )
        p_item->p_meta = vlc_meta_New();
    if( !p_item->p_meta )
        goto end;

    psz_artist = vlc_meta_Get( p_item->p_meta, vlc_meta_Artist );
    psz_album = vlc_meta_Get( p_item->p_meta, vlc_meta_Album );
    psz_arturl = vlc_meta_Get( p_item->p_meta, vlc_meta_ArtworkURL );
    psz_title = vlc_meta_Get( p_item->p_meta, vlc_meta_Title );
    psz_date = vlc_meta_Get( p_item->p_meta, vlc_meta_Date );
    if( !psz_title )
        psz_title = p_item->psz_name;

    if( (EMPTY_STR(psz_artist) || EMPTY_STR(psz_album) ) && !psz_arturl )
        goto end;

    psz_path = ArtCacheGetDirPath( psz_arturl, psz_artist, psz_album, psz_date, psz_title );

end:
    vlc_mutex_unlock( &p_item->lock );
    return psz_path;
}
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
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  album_cache; } ;
typedef  TYPE_1__ input_fetcher_t ;

/* Variables and functions */
 char* CreateCacheKey (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_item_SetArtURL (int /*<<< orphan*/ *,char const*) ; 
 char* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ReadAlbumCache( input_fetcher_t* fetcher, input_item_t* item )
{
    char* key = CreateCacheKey( item );

    if( key == NULL )
        return VLC_EGENERIC;

    vlc_mutex_lock( &fetcher->lock );
    char const* art = vlc_dictionary_value_for_key( &fetcher->album_cache,
                                                    key );
    if( art )
        input_item_SetArtURL( item, art );
    vlc_mutex_unlock( &fetcher->lock );

    free( key );
    return art ? VLC_SUCCESS : VLC_EGENERIC;
}
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
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetArtURL (int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  vlc_dictionary_has_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AddAlbumCache( input_fetcher_t* fetcher, input_item_t* item,
                           bool overwrite )
{
    char* art = input_item_GetArtURL( item );
    char* key = CreateCacheKey( item );

    if( key && art && strncasecmp( art, "attachment://", 13 ) )
    {
        vlc_mutex_lock( &fetcher->lock );
        if( overwrite || !vlc_dictionary_has_key( &fetcher->album_cache, key ) )
        {
            vlc_dictionary_insert( &fetcher->album_cache, key, art );
            art = NULL;
        }
        vlc_mutex_unlock( &fetcher->lock );
    }

    free( art );
    free( key );
}
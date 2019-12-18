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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  p_meta; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  vlc_meta_Album ; 
 int /*<<< orphan*/  vlc_meta_Artist ; 
 int /*<<< orphan*/  vlc_meta_Date ; 
 char* vlc_meta_Get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char* CreateCacheKey( input_item_t* item )
{
    vlc_mutex_lock( &item->lock );

    if( !item->p_meta )
    {
        vlc_mutex_unlock( &item->lock );
        return NULL;
    }

    char const* artist = vlc_meta_Get( item->p_meta, vlc_meta_Artist );
    char const* album = vlc_meta_Get( item->p_meta, vlc_meta_Album );
    char const *date = vlc_meta_Get( item->p_meta, vlc_meta_Date );
    char* key;

    /**
     * Simple concatenation of artist and album can lead to the same key
     * for entities that should not have such. Imagine { dogs, tick } and
     * { dog, stick } */
    if( !artist || !album || asprintf( &key, "%s:%zu:%s:%zu:%s",
          artist, strlen( artist ), album, strlen( album ),
          date ? date : "0000" ) < 0 )
    {
        key = NULL;
    }
    vlc_mutex_unlock( &item->lock );

    return key;
}
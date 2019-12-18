#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  vlc_meta_ESNowPlaying ; 
 int /*<<< orphan*/  vlc_meta_NowPlaying ; 

char *input_item_GetNowPlayingFb( input_item_t *p_item )
{
    char *psz_meta = input_item_GetMeta( p_item, vlc_meta_NowPlaying );
    if( !psz_meta || strlen( psz_meta ) == 0 )
    {
        free( psz_meta );
        return input_item_GetMeta( p_item, vlc_meta_ESNowPlaying );
    }

    return psz_meta;
}
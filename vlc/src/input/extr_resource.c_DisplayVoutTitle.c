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
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_input; } ;
typedef  TYPE_1__ input_resource_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_GetItem (int /*<<< orphan*/ *) ; 
 char* input_item_GetArtist (int /*<<< orphan*/ *) ; 
 char* input_item_GetName (int /*<<< orphan*/ *) ; 
 char* input_item_GetNowPlayingFb (int /*<<< orphan*/ *) ; 
 char* input_item_GetTitle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_DisplayTitle (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void DisplayVoutTitle( input_resource_t *p_resource,
                              vout_thread_t *p_vout )
{
    if( p_resource->p_input == NULL )
        return;

    /* TODO display the title only one time for the same input ? */

    input_item_t *p_item = input_GetItem( p_resource->p_input );

    char *psz_nowplaying = input_item_GetNowPlayingFb( p_item );
    if( psz_nowplaying && *psz_nowplaying )
    {
        vout_DisplayTitle( p_vout, psz_nowplaying );
    }
    else
    {
        char *psz_artist = input_item_GetArtist( p_item );
        char *psz_name = input_item_GetTitle( p_item );

        if( !psz_name || *psz_name == '\0' )
        {
            free( psz_name );
            psz_name = input_item_GetName( p_item );
        }
        if( psz_artist && *psz_artist )
        {
            char *psz_string;
            if( asprintf( &psz_string, "%s - %s", psz_name, psz_artist ) != -1 )
            {
                vout_DisplayTitle( p_vout, psz_string );
                free( psz_string );
            }
        }
        else if( psz_name )
        {
            vout_DisplayTitle( p_vout, psz_name );
        }
        free( psz_name );
        free( psz_artist );
    }
    free( psz_nowplaying );
}
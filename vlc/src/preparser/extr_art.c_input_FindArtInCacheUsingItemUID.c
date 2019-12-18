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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* GetDirByItemUIDs (char*) ; 
 char* GetFileByItemUID (char*,char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetInfo (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  input_item_SetArtURL (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

int input_FindArtInCacheUsingItemUID( input_item_t *p_item )
{
    char *uid = input_item_GetInfo( p_item, "uid", "md5" );
    if ( ! *uid )
    {
        free( uid );
        return VLC_EGENERIC;
    }

    /* we have an input item uid set */
    bool b_done = false;
    char *psz_byuiddir = GetDirByItemUIDs( uid );
    char *psz_byuidfile = GetFileByItemUID( psz_byuiddir, "arturl" );
    free( psz_byuiddir );
    if( psz_byuidfile )
    {
        FILE *fd = vlc_fopen( psz_byuidfile, "rb" );
        if ( fd )
        {
            char sz_cachefile[2049];
            /* read the cache hash url */
            if ( fgets( sz_cachefile, 2048, fd ) != NULL )
            {
                input_item_SetArtURL( p_item, sz_cachefile );
                b_done = true;
            }
            fclose( fd );
        }
        free( psz_byuidfile );
    }
    free( uid );
    if ( b_done ) return VLC_SUCCESS;

    return VLC_EGENERIC;
}
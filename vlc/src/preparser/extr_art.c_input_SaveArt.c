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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ArtCacheCreateDir (char*) ; 
 char* ArtCacheName (int /*<<< orphan*/ *,char const*) ; 
 char* GetDirByItemUIDs (char*) ; 
 char* GetFileByItemUID (char*,char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ *) ; 
 char* input_item_GetInfo (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  input_item_SetArtURL (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 
 char* vlc_path2uri (char*,char*) ; 
 int /*<<< orphan*/  vlc_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int input_SaveArt( vlc_object_t *obj, input_item_t *p_item,
                   const void *data, size_t length, const char *psz_type )
{
    char *psz_filename = ArtCacheName( p_item, psz_type );

    if( !psz_filename )
        return VLC_EGENERIC;

    char *psz_uri = vlc_path2uri( psz_filename, "file" );
    if( !psz_uri )
    {
        free( psz_filename );
        return VLC_EGENERIC;
    }

    /* Check if we already dumped it */
    struct stat s;
    if( !vlc_stat( psz_filename, &s ) )
    {
        input_item_SetArtURL( p_item, psz_uri );
        free( psz_filename );
        free( psz_uri );
        return VLC_SUCCESS;
    }

    /* Dump it otherwise */
    FILE *f = vlc_fopen( psz_filename, "wb" );
    if( f )
    {
        if( fwrite( data, 1, length, f ) != length )
        {
            msg_Err( obj, "%s: %s", psz_filename, vlc_strerror_c(errno) );
        }
        else
        {
            msg_Dbg( obj, "album art saved to %s", psz_filename );
            input_item_SetArtURL( p_item, psz_uri );
        }
        fclose( f );
    }
    free( psz_uri );

    /* save uid info */
    char *uid = input_item_GetInfo( p_item, "uid", "md5" );
    if ( ! *uid )
    {
        free( uid );
        goto end;
    }

    char *psz_byuiddir = GetDirByItemUIDs( uid );
    char *psz_byuidfile = GetFileByItemUID( psz_byuiddir, "arturl" );
    ArtCacheCreateDir( psz_byuiddir );
    free( psz_byuiddir );

    if ( psz_byuidfile )
    {
        f = vlc_fopen( psz_byuidfile, "wb" );
        if ( f )
        {
            if( fputs( "file://", f ) < 0 || fputs( psz_filename, f ) < 0 )
                msg_Err( obj, "Error writing %s: %s", psz_byuidfile,
                         vlc_strerror_c(errno) );
            fclose( f );
        }
        free( psz_byuidfile );
    }
    free( uid );
    /* !save uid info */
end:
    free( psz_filename );
    return VLC_SUCCESS;
}
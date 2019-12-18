#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vlc_memstream {char* ptr; int /*<<< orphan*/  length; } ;
struct fetcher_request {int /*<<< orphan*/  item; } ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ input_fetcher_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AddAlbumCache (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FREENULL (char*) ; 
 int /*<<< orphan*/  NotifyArtFetchEnded (struct fetcher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadAlbumCache (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_SaveArt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* input_item_GetArtURL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_SetArtFetched (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_killed () ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 int /*<<< orphan*/  vlc_memstream_open (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_write (struct vlc_memstream*,char*,int) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_NewURL (int /*<<< orphan*/ ,char*) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void Downloader( input_fetcher_t* fetcher,
    struct fetcher_request* req )
{
    ReadAlbumCache( fetcher, req->item );

    char *psz_arturl = input_item_GetArtURL( req->item );
    if( !psz_arturl )
        goto error;

    if( !strncasecmp( psz_arturl, "file://", 7 ) ||
        !strncasecmp( psz_arturl, "attachment://", 13 ) )
        goto out; /* no fetch required */

    stream_t* source = vlc_stream_NewURL( fetcher->owner, psz_arturl );

    if( !source )
        goto error;

    struct vlc_memstream output_stream;
    vlc_memstream_open( &output_stream );

    for( ;; )
    {
        char buffer[2048];

        int read = vlc_stream_Read( source, buffer, sizeof( buffer ) );
        if( read <= 0 )
            break;

        if( (int)vlc_memstream_write( &output_stream, buffer, read ) < read )
            break;
    }

    vlc_stream_Delete( source );

    if( vlc_memstream_close( &output_stream ) )
        goto error;

    if( vlc_killed() )
    {
        free( output_stream.ptr );
        goto error;
    }

    input_SaveArt( fetcher->owner, req->item, output_stream.ptr,
                   output_stream.length, NULL );

    free( output_stream.ptr );
    AddAlbumCache( fetcher, req->item, true );

out:
    if( psz_arturl )
    {
        var_SetAddress( fetcher->owner, "item-change", req->item );
        input_item_SetArtFetched( req->item, true );
    }

    free( psz_arturl );
    NotifyArtFetchEnded(req, psz_arturl != NULL);
    return;

error:
    FREENULL( psz_arturl );
    goto out;
}
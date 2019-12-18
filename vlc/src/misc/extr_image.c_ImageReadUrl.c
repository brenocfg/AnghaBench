#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/  video_format_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_parent; } ;
typedef  TYPE_1__ image_handler_t ;
typedef  int /*<<< orphan*/  es_format_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ImageRead (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ image_Ext2Fourcc (char const*) ; 
 scalar_t__ image_Mime2Fourcc (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 char* stream_MimeType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_Block (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stream_GetSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * vlc_stream_NewURL (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static picture_t *ImageReadUrl( image_handler_t *p_image, const char *psz_url,
                                video_format_t *p_fmt_out )
{
    block_t *p_block;
    picture_t *p_pic;
    stream_t *p_stream = NULL;
    uint64_t i_size;

    p_stream = vlc_stream_NewURL( p_image->p_parent, psz_url );

    if( !p_stream )
    {
        msg_Dbg( p_image->p_parent, "could not open %s for reading",
                 psz_url );
        return NULL;
    }

    if( vlc_stream_GetSize( p_stream, &i_size ) || i_size > SSIZE_MAX )
    {
        msg_Dbg( p_image->p_parent, "could not read %s", psz_url );
        goto error;
    }

    p_block = vlc_stream_Block( p_stream, i_size );
    if( p_block == NULL )
        goto error;

    vlc_fourcc_t i_chroma = 0;
    char *psz_mime = stream_MimeType( p_stream );
    if( psz_mime != NULL )
    {
        i_chroma = image_Mime2Fourcc( psz_mime );
        free( psz_mime );
    }
    if( !i_chroma )
    {
       /* Try to guess format from file name */
       i_chroma = image_Ext2Fourcc( psz_url );
    }
    vlc_stream_Delete( p_stream );


    es_format_t fmtin;
    es_format_Init( &fmtin, VIDEO_ES, i_chroma );
    p_pic = ImageRead( p_image, p_block, &fmtin, p_fmt_out );

    es_format_Clean( &fmtin );

    return p_pic;
error:
    vlc_stream_Delete( p_stream );
    return NULL;
}
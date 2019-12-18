#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_13__ {int /*<<< orphan*/  p_parent; } ;
typedef  TYPE_2__ image_handler_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_3__* ImageWrite (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ image_Ext2Fourcc (char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int) ; 

__attribute__((used)) static int ImageWriteUrl( image_handler_t *p_image, picture_t *p_pic,
                          const video_format_t *p_fmt_in, const video_format_t *p_fmt_out,
                          const char *psz_url )
{
    block_t *p_block;
    FILE *file;
    video_format_t fmt_out = *p_fmt_out;

    if( !fmt_out.i_chroma )
    {
        /* Try to guess format from file name */
        fmt_out.i_chroma = image_Ext2Fourcc( psz_url );
    }

    file = vlc_fopen( psz_url, "wb" );
    if( !file )
    {
        msg_Err( p_image->p_parent, "%s: %s", psz_url, vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    p_block = ImageWrite( p_image, p_pic, p_fmt_in, &fmt_out );

    int err = 0;
    if( p_block )
    {
        if( fwrite( p_block->p_buffer, p_block->i_buffer, 1, file ) != 1 )
            err = errno;
        block_Release( p_block );
    }

    if( fclose( file ) && !err )
        err = errno;

    if( err )
    {
       errno = err;
       msg_Err( p_image->p_parent, "%s: %s", psz_url, vlc_strerror_c(errno) );
    }

    return err ? VLC_EGENERIC : VLC_SUCCESS;
}
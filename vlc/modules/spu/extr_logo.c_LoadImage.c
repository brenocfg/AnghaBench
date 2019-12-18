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
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  image_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * image_HandlerCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * image_ReadUrl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static picture_t *LoadImage( vlc_object_t *p_this, const char *psz_filename )
{
    if( !psz_filename )
        return NULL;

    image_handler_t *p_image = image_HandlerCreate( p_this );
    if( !p_image )
        return NULL;

    video_format_t fmt_out;
    video_format_Init( &fmt_out, VLC_CODEC_YUVA );

    char *psz_url = vlc_path2uri( psz_filename, NULL );
    picture_t *p_pic = image_ReadUrl( p_image, psz_url, &fmt_out );
    free( psz_url );
    image_HandlerDelete( p_image );
    video_format_Clean( &fmt_out );

    return p_pic;
}
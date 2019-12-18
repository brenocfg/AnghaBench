#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {scalar_t__ p_mask; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * image_HandlerCreate (TYPE_1__*) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ image_ReadUrl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LoadMask( filter_t *p_filter, const char *psz_filename )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    image_handler_t *p_image;
    video_format_t fmt_out;
    video_format_Init( &fmt_out, VLC_CODEC_YUVA );
    if( p_sys->p_mask )
        picture_Release( p_sys->p_mask );
    p_image = image_HandlerCreate( p_filter );
    char *psz_url = vlc_path2uri( psz_filename, NULL );
    p_sys->p_mask =
        image_ReadUrl( p_image, psz_url, &fmt_out );
    free( psz_url );
    video_format_Clean( &fmt_out );
    image_HandlerDelete( p_image );
}
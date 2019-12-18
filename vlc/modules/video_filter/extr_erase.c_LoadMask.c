#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_mask; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * image_HandlerCreate (TYPE_1__*) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * image_ReadUrl (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LoadMask( filter_t *p_filter, const char *psz_filename )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    image_handler_t *p_image;
    video_format_t fmt_out;
    picture_t *p_old_mask = p_sys->p_mask;
    video_format_Init( &fmt_out, VLC_CODEC_YUVA );
    p_image = image_HandlerCreate( p_filter );
    char *psz_url = vlc_path2uri( psz_filename, NULL );
    p_sys->p_mask = image_ReadUrl( p_image, psz_url, &fmt_out );
    free( psz_url );
    video_format_Clean( &fmt_out );
    if( p_sys->p_mask )
    {
        if( p_old_mask )
            picture_Release( p_old_mask );
    }
    else if( p_old_mask )
    {
        p_sys->p_mask = p_old_mask;
        msg_Err( p_filter, "Error while loading new mask. Keeping old mask." );
    }
    else
        msg_Err( p_filter, "Error while loading new mask. No mask available." );

    image_HandlerDelete( p_image );
}
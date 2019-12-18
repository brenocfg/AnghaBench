#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t libvlc_meta_t ;
struct TYPE_5__ {TYPE_3__* p_input_item; } ;
typedef  TYPE_1__ libvlc_media_t ;
struct TYPE_6__ {int /*<<< orphan*/ * psz_name; } ;

/* Variables and functions */
 char* input_item_GetMeta (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* input_item_GetNowPlayingFb (TYPE_3__*) ; 
 size_t libvlc_meta_NowPlaying ; 
 size_t libvlc_meta_Title ; 
 int /*<<< orphan*/ * libvlc_to_vlc_meta ; 
 char* strdup (int /*<<< orphan*/ *) ; 

char *libvlc_media_get_meta( libvlc_media_t *p_md, libvlc_meta_t e_meta )
{
    char *psz_meta = NULL;

    if( e_meta == libvlc_meta_NowPlaying )
    {
        psz_meta = input_item_GetNowPlayingFb( p_md->p_input_item );
    }
    else
    {
        psz_meta = input_item_GetMeta( p_md->p_input_item,
                                             libvlc_to_vlc_meta[e_meta] );
        /* Should be integrated in core */
        if( psz_meta == NULL && e_meta == libvlc_meta_Title
         && p_md->p_input_item->psz_name != NULL )
            psz_meta = strdup( p_md->p_input_item->psz_name );
    }
    return psz_meta;
}
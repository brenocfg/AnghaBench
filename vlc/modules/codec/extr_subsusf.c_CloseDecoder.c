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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_6__ {int i_ssa_styles; int i_images; struct TYPE_6__** pp_images; struct TYPE_6__* psz_filename; scalar_t__ p_pic; struct TYPE_6__** pp_ssa_styles; int /*<<< orphan*/  p_style; struct TYPE_6__* psz_stylename; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_2__**) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_Release (scalar_t__) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CloseDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_sys->pp_ssa_styles )
    {
        for( int i = 0; i < p_sys->i_ssa_styles; i++ )
        {
            if( !p_sys->pp_ssa_styles[i] )
                continue;

            free( p_sys->pp_ssa_styles[i]->psz_stylename );
            text_style_Delete( p_sys->pp_ssa_styles[i]->p_style );
            free( p_sys->pp_ssa_styles[i] );
        }
        TAB_CLEAN( p_sys->i_ssa_styles, p_sys->pp_ssa_styles );
    }
    if( p_sys->pp_images )
    {
        for( int i = 0; i < p_sys->i_images; i++ )
        {
            if( !p_sys->pp_images[i] )
                continue;

            if( p_sys->pp_images[i]->p_pic )
                picture_Release( p_sys->pp_images[i]->p_pic );
            free( p_sys->pp_images[i]->psz_filename );

            free( p_sys->pp_images[i] );
        }
        TAB_CLEAN( p_sys->i_images, p_sys->pp_images );
    }

    free( p_sys );
}
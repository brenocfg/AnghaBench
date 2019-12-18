#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ i_start; scalar_t__ i_stop; int b_ephemer; int b_absolute; int /*<<< orphan*/  i_original_picture_height; int /*<<< orphan*/  i_original_picture_width; int /*<<< orphan*/  p_region; } ;
typedef  TYPE_1__ subpicture_t ;
struct TYPE_14__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_original_height; int /*<<< orphan*/  i_original_width; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_16__ {int i_flags; scalar_t__ i_pts; int i_buffer; scalar_t__ i_length; scalar_t__ p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int /*<<< orphan*/ * EnsureUTF8 (char*) ; 
 int /*<<< orphan*/  ParseUSFString (TYPE_2__*,char*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 TYPE_1__* decoder_NewSubpicture (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 char* strndup (char const*,int) ; 

__attribute__((used)) static subpicture_t *ParseText( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    subpicture_t *p_spu = NULL;
    char *psz_subtitle = NULL;

    if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
        return NULL;

    /* We cannot display a subpicture with no date */
    if( p_block->i_pts == VLC_TICK_INVALID )
    {
        msg_Warn( p_dec, "subtitle without a date" );
        return NULL;
    }

    /* Check validity of packet data */
    /* An "empty" line containing only \0 can be used to force
       and ephemer picture from the screen */
    if( p_block->i_buffer < 1 )
    {
        msg_Warn( p_dec, "no subtitle data" );
        return NULL;
    }

    /* Should be resiliant against bad subtitles */
    psz_subtitle = strndup( (const char *)p_block->p_buffer,
                            p_block->i_buffer );
    if( psz_subtitle == NULL )
        return NULL;

    /* USF Subtitles are mandated to be UTF-8 -- make sure it is */
    if (EnsureUTF8( psz_subtitle ) == NULL)
    {
        msg_Err( p_dec, "USF subtitles must be in UTF-8 format.\n"
                 "This stream contains USF subtitles which aren't." );
    }

    /* Create the subpicture unit */
    p_spu = decoder_NewSubpicture( p_dec, NULL );
    if( !p_spu )
    {
        msg_Warn( p_dec, "can't get spu buffer" );
        free( psz_subtitle );
        return NULL;
    }

    /* Decode USF strings */
    p_spu->p_region = ParseUSFString( p_dec, psz_subtitle );

    p_spu->i_start = p_block->i_pts;
    p_spu->i_stop = p_block->i_pts + p_block->i_length;
    p_spu->b_ephemer = (p_block->i_length == VLC_TICK_INVALID);
    p_spu->b_absolute = false;
    p_spu->i_original_picture_width = p_sys->i_original_width;
    p_spu->i_original_picture_height = p_sys->i_original_height;

    free( psz_subtitle );

    return p_spu;
}
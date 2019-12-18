#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct picture_free_t {TYPE_1__* p_pic; } ;
struct TYPE_25__ {scalar_t__ date; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_26__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_27__ {scalar_t__ i_lastpts; scalar_t__ i_frame_pts_delta; int /*<<< orphan*/  p_schro; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_28__ {int i_flags; scalar_t__ i_pts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_31__ {int /*<<< orphan*/  tag; TYPE_4__* priv; int /*<<< orphan*/  free; } ;
struct TYPE_30__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_29__ {scalar_t__ value; } ;
typedef  TYPE_5__ SchroTag ;
typedef  TYPE_6__ SchroFrame ;
typedef  TYPE_7__ SchroBuffer ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 TYPE_6__* CreateSchroFrameFromPic (TYPE_2__*) ; 
 int /*<<< orphan*/  Flush (TYPE_2__*) ; 
#define  SCHRO_DECODER_EOS 133 
#define  SCHRO_DECODER_ERROR 132 
#define  SCHRO_DECODER_FIRST_ACCESS_UNIT 131 
#define  SCHRO_DECODER_NEED_BITS 130 
#define  SCHRO_DECODER_NEED_FRAME 129 
#define  SCHRO_DECODER_OK 128 
 int /*<<< orphan*/  SchroBufferFree ; 
 int /*<<< orphan*/  SetVideoFormat (TYPE_2__*) ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  decoder_QueueVideo (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  free ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 TYPE_7__* schro_buffer_new_with_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schro_decoder_add_output_picture (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  schro_decoder_autoparse_push (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int schro_decoder_autoparse_wait (int /*<<< orphan*/ ) ; 
 TYPE_5__* schro_decoder_get_picture_tag (int /*<<< orphan*/ ) ; 
 TYPE_6__* schro_decoder_pull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schro_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  schro_tag_free (TYPE_5__*) ; 
 int /*<<< orphan*/  schro_tag_new (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( !p_block ) /* No Drain */
        return VLCDEC_SUCCESS;
    else {

        /* reset the decoder when seeking as the decode in progress is invalid */
        /* discard the block as it is just a null magic block */
        if( p_block->i_flags & (BLOCK_FLAG_CORRUPTED|BLOCK_FLAG_DISCONTINUITY) )
        {
            Flush( p_dec );
            if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
            {
                block_Release( p_block );
                return VLCDEC_SUCCESS;
            }
        }

        SchroBuffer *p_schrobuffer;
        p_schrobuffer = schro_buffer_new_with_data( p_block->p_buffer, p_block->i_buffer );
        p_schrobuffer->free = SchroBufferFree;
        p_schrobuffer->priv = p_block;
        if( p_block->i_pts != VLC_TICK_INVALID ) {
            vlc_tick_t *p_pts = malloc( sizeof(*p_pts) );
            if( p_pts ) {
                *p_pts = p_block->i_pts;
                /* if this call fails, p_pts is freed automatically */
                p_schrobuffer->tag = schro_tag_new( p_pts, free );
            }
        }

        /* this stops the same block being fed back into this function if
         * we were on the next iteration of this loop to output a picture */
        schro_decoder_autoparse_push( p_sys->p_schro, p_schrobuffer );
        /* DO NOT refer to p_block after this point, it may have been freed */
    }

    while( 1 )
    {
        SchroFrame *p_schroframe;
        picture_t *p_pic;
        int state = schro_decoder_autoparse_wait( p_sys->p_schro );

        switch( state )
        {
        case SCHRO_DECODER_FIRST_ACCESS_UNIT:
            SetVideoFormat( p_dec );
            break;

        case SCHRO_DECODER_NEED_BITS:
            return VLCDEC_SUCCESS;

        case SCHRO_DECODER_NEED_FRAME:
            p_schroframe = CreateSchroFrameFromPic( p_dec );

            if( !p_schroframe )
            {
                msg_Err( p_dec, "Could not allocate picture for decoder");
                return VLCDEC_SUCCESS;
            }

            schro_decoder_add_output_picture( p_sys->p_schro, p_schroframe);
            break;

        case SCHRO_DECODER_OK: {
            SchroTag *p_tag = schro_decoder_get_picture_tag( p_sys->p_schro );
            p_schroframe = schro_decoder_pull( p_sys->p_schro );
            if( !p_schroframe || !p_schroframe->priv )
            {
                /* frame can't be one that was allocated by us
                 *   -- no private data: discard */
                if( p_tag ) schro_tag_free( p_tag );
                if( p_schroframe ) schro_frame_unref( p_schroframe );
                break;
            }
            p_pic = ((struct picture_free_t*) p_schroframe->priv)->p_pic;
            p_schroframe->priv = NULL;

            if( p_tag )
            {
                /* free is handled by schro_frame_unref */
                p_pic->date = *(vlc_tick_t*) p_tag->value;
                schro_tag_free( p_tag );
            }
            else if( p_sys->i_lastpts != VLC_TICK_INVALID )
            {
                /* NB, this shouldn't happen since the packetizer does a
                 * very thorough job of inventing timestamps.  The
                 * following is just a very rough fall back incase packetizer
                 * is missing. */
                /* maybe it would be better to set p_pic->b_force ? */
                p_pic->date = p_sys->i_lastpts + p_sys->i_frame_pts_delta;
            }
            p_sys->i_lastpts = p_pic->date;

            schro_frame_unref( p_schroframe );
            decoder_QueueVideo( p_dec, p_pic );
            return VLCDEC_SUCCESS;
        }
        case SCHRO_DECODER_EOS:
            /* NB, the new api will not emit _EOS, it handles the reset internally */
            break;

        case SCHRO_DECODER_ERROR:
            msg_Err( p_dec, "SCHRO_DECODER_ERROR");
            return VLCDEC_SUCCESS;
        }
    }
}
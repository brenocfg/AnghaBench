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
typedef  int /*<<< orphan*/  th_ycbcr_buffer ;
struct TYPE_13__ {int b_progressive; int /*<<< orphan*/  date; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_14__ {int* packet; } ;
typedef  TYPE_2__ ogg_packet ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_16__ {int b_decoded_first_keyframe; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  tcx; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 TYPE_1__* decoder_NewPicture (TYPE_3__*) ; 
 scalar_t__ decoder_UpdateVideoFormat (TYPE_3__*) ; 
 scalar_t__ th_decode_packetin (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ th_decode_ycbcr_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  theora_CopyPicture (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *DecodePacket( decoder_t *p_dec, ogg_packet *p_oggpacket )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    picture_t *p_pic;
    th_ycbcr_buffer ycbcr;

    /* TODO: Implement _granpos (3rd parameter here) and add the
     * call to TH_DECCTL_SET_GRANDPOS after seek */
    /* TODO: If the return is TH_DUPFRAME, we don't need to display a new
     * frame, but we do need to keep displaying the previous one. */
    if (th_decode_packetin( p_sys->tcx, p_oggpacket, NULL ) < 0)
        return NULL; /* bad packet */

    /* Check for keyframe */
    if( !(p_oggpacket->packet[0] & 0x80) /* data packet */ &&
        !(p_oggpacket->packet[0] & 0x40) /* intra frame */ )
        p_sys->b_decoded_first_keyframe = true;

    /* If we haven't seen a single keyframe yet, don't let Theora decode
     * anything, otherwise we'll get display artifacts.  (This is impossible
     * in the general case, but can happen if e.g. we play a network stream
     * using a timed URL, such that the server doesn't start the video with a
     * keyframe). */
    if( !p_sys->b_decoded_first_keyframe )
        return NULL; /* Wait until we've decoded the first keyframe */

    if( th_decode_ycbcr_out( p_sys->tcx, ycbcr ) ) /* returns 0 on success */
        return NULL;

    /* Get a new picture */
    if( decoder_UpdateVideoFormat( p_dec ) )
        return NULL;
    p_pic = decoder_NewPicture( p_dec );
    if( !p_pic ) return NULL;

    theora_CopyPicture( p_pic, ycbcr );

    p_pic->date = p_sys->i_pts;
    p_pic->b_progressive = true;

    return p_pic;
}
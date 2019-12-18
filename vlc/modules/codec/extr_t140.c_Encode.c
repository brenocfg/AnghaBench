#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * psz_text; struct TYPE_10__* p_next; } ;
typedef  TYPE_2__ text_segment_t ;
struct TYPE_11__ {scalar_t__ i_start; scalar_t__ i_stop; int /*<<< orphan*/  b_ephemer; TYPE_4__* p_region; } ;
typedef  TYPE_3__ subpicture_t ;
struct TYPE_9__ {scalar_t__ i_chroma; } ;
struct TYPE_12__ {TYPE_2__* p_text; TYPE_1__ fmt; } ;
typedef  TYPE_4__ subpicture_region_t ;
typedef  int /*<<< orphan*/  encoder_t ;
struct TYPE_13__ {size_t i_buffer; scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ i_length; scalar_t__* p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_TEXT ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *Encode( encoder_t *p_enc, subpicture_t *p_spu )
{
    VLC_UNUSED( p_enc );

    subpicture_region_t *p_region;
    block_t *p_block;
    size_t len = 0;

    if( p_spu == NULL )
        return NULL;

    p_region = p_spu->p_region;
    if( ( p_region == NULL )
     || ( p_region->fmt.i_chroma != VLC_CODEC_TEXT )
     || ( p_region->p_text == NULL )
     || ( p_region->p_text->psz_text == NULL) )
        return NULL;

    /* This should already be UTF-8 encoded, so not much effort... */
    for( const text_segment_t *p_segment = p_region->p_text;
                               p_segment; p_segment = p_segment->p_next )
    {
        if( p_segment->psz_text == NULL )
            continue;
        len += strlen( p_segment->psz_text );
    }

    p_block = block_Alloc( len + 1 );
    if( !p_block )
        return NULL;

    p_block->i_buffer = 0;
    for( const text_segment_t *p_segment = p_region->p_text;
                               p_segment; p_segment = p_segment->p_next )
    {
        if( p_segment->psz_text == NULL )
            continue;
        len = strlen( p_segment->psz_text );
        memcpy( &p_block->p_buffer[p_block->i_buffer],
                p_segment->psz_text, len );
        p_block->i_buffer += len;
    }
    p_block->p_buffer[p_block->i_buffer] = 0;

    p_block->i_pts = p_block->i_dts = p_spu->i_start;
    if( !p_spu->b_ephemer && ( p_spu->i_stop > p_spu->i_start ) )
        p_block->i_length = p_spu->i_stop - p_spu->i_start;

    return p_block;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_8__ {int i_spu_size; int metadata_offset; int metadata_length; int i_image_offset; int i_image_length; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_9__ {int* p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int,int) ; 

__attribute__((used)) static void ParseHeader( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    uint8_t *p = p_block->p_buffer;

    p_sys->i_spu_size = (p[0] << 8) + p[1] + 4; p += 2;

    /* FIXME: check data sanity */
    p_sys->metadata_offset = (p[0] <<  8) +   p[1]; p +=2;
    p_sys->metadata_length = p_sys->i_spu_size - p_sys->metadata_offset;

    p_sys->i_image_offset = 4;
    p_sys->i_image_length = p_sys->metadata_offset - p_sys->i_image_offset;

#ifdef DEBUG_CVDSUB
    msg_Dbg( p_dec, "total size: %zu  image size: %zu",
             p_sys->i_spu_size, p_sys->i_image_length );
#endif
}
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
typedef  int /*<<< orphan*/  transcode_encoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainAppend (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transcode_encoder_audio_encode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int transcode_encoder_audio_drain( transcode_encoder_t *p_enc, block_t **out )
{
    block_t *p_block;
    do {
        p_block = transcode_encoder_audio_encode( p_enc, NULL );
        block_ChainAppend( out, p_block );
    } while( p_block );
    return VLC_SUCCESS;
}
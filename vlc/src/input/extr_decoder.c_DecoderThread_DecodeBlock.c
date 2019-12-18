#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* pf_decode ) (TYPE_1__*,TYPE_2__*) ;} ;
struct decoder_owner {int error; TYPE_1__ dec; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_9__ {int i_flags; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORE_PRIVATE_RELOADED ; 
 int /*<<< orphan*/  DecoderThread_ProcessInput (struct decoder_owner*,TYPE_2__*) ; 
 int /*<<< orphan*/  RequestReload (struct decoder_owner*) ; 
#define  VLCDEC_ECRITICAL 130 
#define  VLCDEC_RELOAD 129 
#define  VLCDEC_SUCCESS 128 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int stub1 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void DecoderThread_DecodeBlock( struct decoder_owner *p_owner, block_t *p_block )
{
    decoder_t *p_dec = &p_owner->dec;

    int ret = p_dec->pf_decode( p_dec, p_block );
    switch( ret )
    {
        case VLCDEC_SUCCESS:
            break;
        case VLCDEC_ECRITICAL:
            p_owner->error = true;
            break;
        case VLCDEC_RELOAD:
            RequestReload( p_owner );
            if( unlikely( p_block == NULL ) )
                break;
            if( !( p_block->i_flags & BLOCK_FLAG_CORE_PRIVATE_RELOADED ) )
            {
                p_block->i_flags |= BLOCK_FLAG_CORE_PRIVATE_RELOADED;
                DecoderThread_ProcessInput( p_owner, p_block );
            }
            else /* We prefer loosing this block than an infinite recursion */
                block_Release( p_block );
            break;
        default:
            vlc_assert_unreachable();
    }
}
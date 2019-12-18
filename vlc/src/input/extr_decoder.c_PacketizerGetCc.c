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
struct TYPE_5__ {int /*<<< orphan*/  b_supported; } ;
struct decoder_owner {TYPE_1__ cc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* pf_get_cc ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ decoder_t ;
typedef  int /*<<< orphan*/  decoder_cc_desc_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecoderPlayCc (struct decoder_owner*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PacketizerGetCc( struct decoder_owner *p_owner, decoder_t *p_dec_cc )
{
    block_t *p_cc;
    decoder_cc_desc_t desc;

    /* Do not try retreiving CC if not wanted (sout) or cannot be retreived */
    if( !p_owner->cc.b_supported )
        return;

    assert( p_dec_cc->pf_get_cc != NULL );

    p_cc = p_dec_cc->pf_get_cc( p_dec_cc, &desc );
    if( !p_cc )
        return;
    DecoderPlayCc( p_owner, p_cc, &desc );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ b_supported; } ;
struct decoder_owner {TYPE_2__* p_packetizer; TYPE_1__ cc; } ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  decoder_cc_desc_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int /*<<< orphan*/  pf_get_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DecoderPlayCc (struct decoder_owner*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ModuleThread_QueueCc( decoder_t *p_videodec, block_t *p_cc,
                                  const decoder_cc_desc_t *p_desc )
{
    struct decoder_owner *p_owner = dec_get_owner( p_videodec );

    if( unlikely( p_cc != NULL ) )
    {
        if( p_owner->cc.b_supported &&
           ( !p_owner->p_packetizer || !p_owner->p_packetizer->pf_get_cc ) )
            DecoderPlayCc( p_owner, p_cc, p_desc );
        else
            block_Release( p_cc );
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_dec; TYPE_3__ fmt; TYPE_1__* p_master; } ;
typedef  TYPE_2__ es_out_id_t ;
struct TYPE_5__ {scalar_t__ p_dec; } ;

/* Variables and functions */
 int EsOutGetClosedCaptionsChannel (TYPE_3__*) ; 
 int /*<<< orphan*/  input_DecoderGetCcState (scalar_t__,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static bool EsIsSelected( es_out_id_t *es )
{
    if( es->p_master )
    {
        bool b_decode = false;
        if( es->p_master->p_dec )
        {
            int i_channel = EsOutGetClosedCaptionsChannel( &es->fmt );
            input_DecoderGetCcState( es->p_master->p_dec, es->fmt.i_codec,
                                     i_channel, &b_decode );
        }
        return b_decode;
    }
    else
    {
        return es->p_dec != NULL;
    }
}
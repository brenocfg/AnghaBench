#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aout_sys_common {scalar_t__ i_out_size; int /*<<< orphan*/ * p_out_chain; int /*<<< orphan*/ ** pp_out_last; } ;
struct TYPE_3__ {scalar_t__ sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ca_ClearOutBuffers(audio_output_t *p_aout)
{
    struct aout_sys_common *p_sys = (struct aout_sys_common *) p_aout->sys;

    block_ChainRelease(p_sys->p_out_chain);
    p_sys->p_out_chain = NULL;
    p_sys->pp_out_last = &p_sys->p_out_chain;

    p_sys->i_out_size = 0;
}
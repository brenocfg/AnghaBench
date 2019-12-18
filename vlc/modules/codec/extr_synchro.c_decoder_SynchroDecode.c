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
struct TYPE_3__ {int /*<<< orphan*/  i_dec_nb_ref; int /*<<< orphan*/  i_nb_ref; int /*<<< orphan*/  decoding_start; } ;
typedef  TYPE_1__ decoder_synchro_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_tick_now () ; 

void decoder_SynchroDecode( decoder_synchro_t * p_synchro )
{
    p_synchro->decoding_start = vlc_tick_now();
    p_synchro->i_nb_ref = p_synchro->i_dec_nb_ref;
}
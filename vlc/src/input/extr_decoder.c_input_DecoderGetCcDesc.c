#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;
struct decoder_owner {int /*<<< orphan*/  lock; TYPE_1__ cc; } ;
typedef  int /*<<< orphan*/  decoder_t ;
typedef  int /*<<< orphan*/  decoder_cc_desc_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_DecoderGetCcDesc( decoder_t *p_dec, decoder_cc_desc_t *p_desc )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    vlc_mutex_lock( &p_owner->lock );
    *p_desc = p_owner->cc.desc;
    vlc_mutex_unlock( &p_owner->lock );
}
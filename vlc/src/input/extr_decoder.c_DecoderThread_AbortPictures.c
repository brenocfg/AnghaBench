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
struct decoder_owner {int /*<<< orphan*/  lock; scalar_t__ out_pool; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_pool_Cancel (scalar_t__,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DecoderThread_AbortPictures( decoder_t *p_dec, bool b_abort )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    vlc_mutex_lock( &p_owner->lock ); // called in DecoderThread
    if (p_owner->out_pool)
        picture_pool_Cancel( p_owner->out_pool, b_abort );
    vlc_mutex_unlock( &p_owner->lock );
}
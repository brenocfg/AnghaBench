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
typedef  int /*<<< orphan*/  vlc_mouse_event ;
struct decoder_owner {int /*<<< orphan*/  mouse_lock; void* mouse_opaque; int /*<<< orphan*/  mouse_event; } ;
struct TYPE_5__ {scalar_t__ i_cat; } ;
struct TYPE_6__ {TYPE_1__ fmt_in; } ;
typedef  TYPE_2__ decoder_t ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  assert (int) ; 
 struct decoder_owner* dec_get_owner (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_DecoderSetVoutMouseEvent( decoder_t *dec, vlc_mouse_event mouse_event,
                                    void *user_data )
{
    struct decoder_owner *owner = dec_get_owner( dec );
    assert( dec->fmt_in.i_cat == VIDEO_ES );

    vlc_mutex_lock( &owner->mouse_lock );

    owner->mouse_event = mouse_event;
    owner->mouse_opaque = user_data;

    vlc_mutex_unlock( &owner->mouse_lock );
}
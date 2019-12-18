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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  unsigned int pa_subscription_event_type_t ;
typedef  int /*<<< orphan*/  pa_context ;
struct TYPE_3__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 unsigned int PA_SUBSCRIPTION_EVENT_FACILITY_MASK ; 
#define  PA_SUBSCRIPTION_EVENT_SINK 129 
#define  PA_SUBSCRIPTION_EVENT_SINK_INPUT 128 
 unsigned int PA_SUBSCRIPTION_EVENT_TYPE_MASK ; 
 int /*<<< orphan*/  pa_stream_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sink_event (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sink_input_event (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void context_cb(pa_context *ctx, pa_subscription_event_type_t type,
                       uint32_t idx, void *userdata)
{
    audio_output_t *aout = userdata;
    aout_sys_t *sys = aout->sys;
    unsigned facility = type & PA_SUBSCRIPTION_EVENT_FACILITY_MASK;

    type &= PA_SUBSCRIPTION_EVENT_TYPE_MASK;
    switch (facility)
    {
        case PA_SUBSCRIPTION_EVENT_SINK:
            sink_event(ctx, type, idx, userdata);
            break;

        case PA_SUBSCRIPTION_EVENT_SINK_INPUT:
            /* only interested in our sink input */
            if (sys->stream != NULL && idx == pa_stream_get_index(sys->stream))
                sink_input_event(ctx, type, idx, userdata);
            break;

        default: /* unsubscribed facility?! */
            vlc_assert_unreachable();
    }
}
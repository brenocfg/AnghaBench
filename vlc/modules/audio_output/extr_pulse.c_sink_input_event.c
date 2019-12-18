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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int pa_subscription_event_type_t ;
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int /*<<< orphan*/  pa_context ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
#define  PA_SUBSCRIPTION_EVENT_REMOVE 128 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pa_context_get_sink_input_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sink_input_info_cb ; 

__attribute__((used)) static void sink_input_event(pa_context *ctx,
                             pa_subscription_event_type_t type,
                             uint32_t idx, audio_output_t *aout)
{
    pa_operation *op;

    /* Gee... PA will not provide the infos directly in the event. */
    switch (type)
    {
        case PA_SUBSCRIPTION_EVENT_REMOVE:
            msg_Err(aout, "sink input killed!");
            break;

        default:
            op = pa_context_get_sink_input_info(ctx, idx, sink_input_info_cb,
                                                aout);
            if (likely(op != NULL))
                pa_operation_unref(op);
            break;
    }
}
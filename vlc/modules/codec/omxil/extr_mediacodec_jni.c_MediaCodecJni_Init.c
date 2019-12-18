#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mc_api_sys ;
struct TYPE_4__ {int b_support_rotation; int /*<<< orphan*/  set_output_surface; int /*<<< orphan*/ * release_out_ts; int /*<<< orphan*/  release_out; int /*<<< orphan*/  get_out; int /*<<< orphan*/  dequeue_out; int /*<<< orphan*/  queue_in; int /*<<< orphan*/  dequeue_in; int /*<<< orphan*/  flush; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  configure_decoder; int /*<<< orphan*/  prepare; int /*<<< orphan*/  clean; int /*<<< orphan*/  p_sys; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ mc_api ;
struct TYPE_5__ {scalar_t__ get_output_buffer; scalar_t__ get_input_buffer; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  Clean ; 
 int /*<<< orphan*/  ConfigureDecoder ; 
 int /*<<< orphan*/  DequeueInput ; 
 int /*<<< orphan*/  DequeueOutput ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  GET_ENV () ; 
 int /*<<< orphan*/  GetOutput ; 
 int /*<<< orphan*/  InitJNIFields (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MC_API_ERROR ; 
 int /*<<< orphan*/  Prepare ; 
 int /*<<< orphan*/  QueueInput ; 
 int /*<<< orphan*/  ReleaseOutput ; 
 int /*<<< orphan*/  SetOutputSurface ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  Stop ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 TYPE_2__ jfields ; 

int MediaCodecJni_Init(mc_api *api)
{
    JNIEnv *env;

    GET_ENV();

    if (!InitJNIFields(api->p_obj, env))
        return MC_API_ERROR;

    api->p_sys = calloc(1, sizeof(mc_api_sys));
    if (!api->p_sys)
        return MC_API_ERROR;

    api->clean = Clean;
    api->prepare = Prepare;
    api->configure_decoder = ConfigureDecoder;
    api->start = Start;
    api->stop = Stop;
    api->flush = Flush;
    api->dequeue_in = DequeueInput;
    api->queue_in = QueueInput;
    api->dequeue_out = DequeueOutput;
    api->get_out = GetOutput;
    api->release_out = ReleaseOutput;
    api->release_out_ts = NULL;
    api->set_output_surface = SetOutputSurface;

    /* Allow rotation only after API 21 */
    if (jfields.get_input_buffer && jfields.get_output_buffer)
        api->b_support_rotation = true;
    return 0;
}
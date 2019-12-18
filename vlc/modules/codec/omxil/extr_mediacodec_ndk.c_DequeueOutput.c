#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  info; int /*<<< orphan*/  p_codec; } ;
typedef  TYPE_2__ mc_api_sys ;
struct TYPE_8__ {int /*<<< orphan*/  p_obj; TYPE_2__* p_sys; } ;
typedef  TYPE_3__ mc_api ;
struct TYPE_6__ {scalar_t__ (* dequeueOutputBuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_1__ AMediaCodec; } ;

/* Variables and functions */
 scalar_t__ AMEDIACODEC_INFO_OUTPUT_BUFFERS_CHANGED ; 
 scalar_t__ AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED ; 
 scalar_t__ AMEDIACODEC_INFO_TRY_AGAIN_LATER ; 
 int MC_API_ERROR ; 
 int MC_API_INFO_OUTPUT_BUFFERS_CHANGED ; 
 int MC_API_INFO_OUTPUT_FORMAT_CHANGED ; 
 int MC_API_INFO_TRYAGAIN ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ syms ; 

__attribute__((used)) static int DequeueOutput(mc_api *api, vlc_tick_t i_timeout)
{
    mc_api_sys *p_sys = api->p_sys;
    ssize_t i_index;

    i_index = syms.AMediaCodec.dequeueOutputBuffer(p_sys->p_codec, &p_sys->info,
                                                   i_timeout);

    if (i_index >= 0)
        return i_index;
    else if (i_index == AMEDIACODEC_INFO_TRY_AGAIN_LATER)
        return MC_API_INFO_TRYAGAIN;
    else if (i_index == AMEDIACODEC_INFO_OUTPUT_BUFFERS_CHANGED)
        return MC_API_INFO_OUTPUT_BUFFERS_CHANGED;
    else if (i_index == AMEDIACODEC_INFO_OUTPUT_FORMAT_CHANGED)
        return MC_API_INFO_OUTPUT_FORMAT_CHANGED;
    else
    {
        msg_Warn(api->p_obj, "AMediaCodec.dequeueOutputBuffer failed");
        return MC_API_ERROR;
    }
}
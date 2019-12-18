#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  p_codec; } ;
typedef  TYPE_2__ mc_api_sys ;
struct TYPE_9__ {int b_started; int /*<<< orphan*/  p_obj; TYPE_2__* p_sys; } ;
typedef  TYPE_3__ mc_api ;
struct TYPE_7__ {scalar_t__ (* start ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_1__ AMediaCodec; } ;

/* Variables and functions */
 scalar_t__ AMEDIA_OK ; 
 int MC_API_ERROR ; 
 int /*<<< orphan*/  Stop (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_4__ syms ; 

__attribute__((used)) static int Start(mc_api *api)
{
    mc_api_sys *p_sys = api->p_sys;
    int i_ret = MC_API_ERROR;

    if (syms.AMediaCodec.start(p_sys->p_codec) != AMEDIA_OK)
    {
        msg_Err(api->p_obj, "AMediaCodec.start failed");
        goto error;
    }

    api->b_started = true;
    i_ret = 0;

    msg_Dbg(api->p_obj, "MediaCodec via NDK opened");
error:
    if (i_ret != 0)
        Stop(api);
    return i_ret;
}
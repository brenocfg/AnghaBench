#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * p_format; int /*<<< orphan*/ * p_codec; } ;
typedef  TYPE_3__ mc_api_sys ;
struct TYPE_10__ {int b_direct_rendering; int b_started; int /*<<< orphan*/  p_obj; TYPE_3__* p_sys; } ;
typedef  TYPE_4__ mc_api ;
struct TYPE_8__ {int /*<<< orphan*/  (* delete ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* delete ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {TYPE_2__ AMediaFormat; TYPE_1__ AMediaCodec; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 TYPE_5__ syms ; 

__attribute__((used)) static int Stop(mc_api *api)
{
    mc_api_sys *p_sys = api->p_sys;

    api->b_direct_rendering = false;

    if (p_sys->p_codec)
    {
        if (api->b_started)
        {
            syms.AMediaCodec.stop(p_sys->p_codec);
            api->b_started = false;
        }
        syms.AMediaCodec.delete(p_sys->p_codec);
        p_sys->p_codec = NULL;
    }
    if (p_sys->p_format)
    {
        syms.AMediaFormat.delete(p_sys->p_format);
        p_sys->p_format = NULL;
    }

    msg_Dbg(api->p_obj, "MediaCodec via NDK closed");
    return 0;
}
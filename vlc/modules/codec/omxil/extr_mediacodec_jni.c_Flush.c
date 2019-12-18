#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  codec; } ;
typedef  TYPE_1__ mc_api_sys ;
struct TYPE_8__ {int /*<<< orphan*/  p_obj; TYPE_1__* p_sys; } ;
typedef  TYPE_2__ mc_api ;
struct TYPE_10__ {int /*<<< orphan*/  flush; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* JNIEnv ;

/* Variables and functions */
 scalar_t__ CHECK_EXCEPTION () ; 
 int /*<<< orphan*/  GET_ENV () ; 
 int MC_API_ERROR ; 
 TYPE_5__ jfields ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Flush(mc_api *api)
{
    mc_api_sys *p_sys = api->p_sys;
    JNIEnv *env = NULL;

    GET_ENV();

    (*env)->CallVoidMethod(env, p_sys->codec, jfields.flush);
    if (CHECK_EXCEPTION())
    {
        msg_Warn(api->p_obj, "Exception occurred in MediaCodec.flush");
        return MC_API_ERROR;
    }
    return 0;
}
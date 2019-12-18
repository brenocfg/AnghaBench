#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AWindow_ID { ____Placeholder_AWindow_ID } AWindow_ID ;
struct TYPE_9__ {TYPE_1__* views; int /*<<< orphan*/  (* pf_winRelease ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/ * jsurface; int /*<<< orphan*/ * p_anw; } ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ AWindowHandler ;

/* Variables and functions */
 int AWindow_Max ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AWindowHandler_releaseANativeWindowEnv(AWindowHandler *p_awh, JNIEnv *p_env,
                                       enum AWindow_ID id)
{
    assert(id < AWindow_Max);

    if (p_awh->views[id].p_anw)
    {
        p_awh->pf_winRelease(p_awh->views[id].p_anw);
        p_awh->views[id].p_anw = NULL;
    }

    if (p_awh->views[id].jsurface)
    {
        (*p_env)->DeleteGlobalRef(p_env, p_awh->views[id].jsurface);
        p_awh->views[id].jsurface = NULL;
    }
}
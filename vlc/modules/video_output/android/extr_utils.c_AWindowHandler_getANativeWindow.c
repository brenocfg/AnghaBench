#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AWindow_ID { ____Placeholder_AWindow_ID } AWindow_ID ;
struct TYPE_7__ {TYPE_1__* views; int /*<<< orphan*/ * (* pf_winFromSurface ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * p_anw; int /*<<< orphan*/ * jsurface; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_2__ AWindowHandler ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */
 int /*<<< orphan*/ * AWindowHandler_getEnv (TYPE_2__*) ; 
 int AWindow_Max ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ WindowHandler_NewSurfaceEnv (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ANativeWindow *
AWindowHandler_getANativeWindow(AWindowHandler *p_awh, enum AWindow_ID id)
{
    assert(id < AWindow_Max);

    JNIEnv *p_env;

    if (p_awh->views[id].p_anw)
        return p_awh->views[id].p_anw;

    p_env = AWindowHandler_getEnv(p_awh);
    if (!p_env)
        return NULL;

    if (WindowHandler_NewSurfaceEnv(p_awh, p_env, id) != VLC_SUCCESS)
        return NULL;
    assert(p_awh->views[id].jsurface != NULL);

    p_awh->views[id].p_anw = p_awh->pf_winFromSurface(p_env,
                                                      p_awh->views[id].jsurface);
    return p_awh->views[id].p_anw;
}
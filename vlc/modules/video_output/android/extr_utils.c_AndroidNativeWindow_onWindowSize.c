#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jlong ;
typedef  int /*<<< orphan*/  jint ;
struct TYPE_5__ {int /*<<< orphan*/  (* on_new_window_size ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  wnd; TYPE_2__ event; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_3__ AWindowHandler ;

/* Variables and functions */
 TYPE_3__* jlong_AWindowHandler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AndroidNativeWindow_onWindowSize(JNIEnv* env, jobject clazz, jlong handle,
                                 jint width, jint height)
{
    (void) env; (void) clazz;
    AWindowHandler *p_awh = jlong_AWindowHandler(handle);

    if (width >= 0 && height >= 0)
        p_awh->event.cb.on_new_window_size(p_awh->wnd, width, height);
}
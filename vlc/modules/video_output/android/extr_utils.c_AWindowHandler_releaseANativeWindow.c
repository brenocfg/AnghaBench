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
typedef  enum AWindow_ID { ____Placeholder_AWindow_ID } AWindow_ID ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  int /*<<< orphan*/  AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/ * AWindowHandler_getEnv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AWindowHandler_releaseANativeWindowEnv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void AWindowHandler_releaseANativeWindow(AWindowHandler *p_awh,
                                         enum AWindow_ID id)
{
    JNIEnv *p_env = AWindowHandler_getEnv(p_awh);
    if (p_env)
        AWindowHandler_releaseANativeWindowEnv(p_awh, p_env, id);
}
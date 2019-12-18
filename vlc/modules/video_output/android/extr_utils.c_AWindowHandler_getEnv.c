#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  p_jvm; } ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_1__ AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/ * android_getEnvCommon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static JNIEnv*
AWindowHandler_getEnv(AWindowHandler *p_awh)
{
    return android_getEnvCommon(NULL, p_awh->p_jvm, "AWindowHandler");
}
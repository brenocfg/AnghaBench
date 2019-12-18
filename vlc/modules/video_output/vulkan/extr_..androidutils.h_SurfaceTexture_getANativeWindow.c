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
typedef  int /*<<< orphan*/  AWindowHandler ;
typedef  int /*<<< orphan*/  ANativeWindow ;

/* Variables and functions */
 int /*<<< orphan*/ * AWindowHandler_getANativeWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWindow_SurfaceTexture ; 

__attribute__((used)) static inline ANativeWindow *
SurfaceTexture_getANativeWindow(AWindowHandler *p_awh)
{
    return AWindowHandler_getANativeWindow(p_awh, AWindow_SurfaceTexture);
}
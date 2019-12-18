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
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  AWindowHandler ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_getSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWindow_SurfaceTexture ; 

__attribute__((used)) static inline jobject
SurfaceTexture_getSurface(AWindowHandler *p_awh)
{
    return AWindowHandler_getSurface(p_awh, AWindow_SurfaceTexture);
}
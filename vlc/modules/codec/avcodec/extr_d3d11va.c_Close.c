#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vlc_va_t ;
struct TYPE_5__ {scalar_t__ va_pool; scalar_t__ vctx; } ;
typedef  TYPE_2__ vlc_va_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  va_pool_Close (scalar_t__) ; 
 int /*<<< orphan*/  vlc_video_context_Release (scalar_t__) ; 

__attribute__((used)) static void Close(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;

    if (sys->vctx)
        vlc_video_context_Release(sys->vctx);

    if (sys->va_pool)
        va_pool_Close(sys->va_pool);
}
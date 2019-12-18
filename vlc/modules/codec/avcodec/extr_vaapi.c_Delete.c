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
struct TYPE_5__ {int /*<<< orphan*/  va_pool; int /*<<< orphan*/  vctx; } ;
typedef  TYPE_2__ vlc_va_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  va_pool_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_video_context_Release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Delete(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;

    vlc_video_context_Release(sys->vctx);
    va_pool_Close(sys->va_pool);
}
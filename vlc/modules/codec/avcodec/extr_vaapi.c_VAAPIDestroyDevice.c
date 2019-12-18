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
struct TYPE_4__ {scalar_t__ context_id; scalar_t__ config_id; int /*<<< orphan*/  display; } ;
struct TYPE_5__ {TYPE_1__ hw_ctx; } ;
typedef  TYPE_2__ vlc_va_sys_t ;

/* Variables and functions */
 scalar_t__ VA_INVALID_ID ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void VAAPIDestroyDevice(void *opaque)
{
    vlc_va_sys_t *sys = opaque;
    if (sys->hw_ctx.context_id != VA_INVALID_ID)
        vlc_vaapi_DestroyContext(NULL, sys->hw_ctx.display, sys->hw_ctx.context_id);
    if (sys->hw_ctx.config_id != VA_INVALID_ID)
        vlc_vaapi_DestroyConfig(NULL, sys->hw_ctx.display, sys->hw_ctx.config_id);
    free(sys);
}
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
struct TYPE_5__ {TYPE_1__* window; } ;
typedef  TYPE_2__ vlc_vk_t ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VOUT_WINDOW_TYPE_HWND ; 

int vlc_vk_InitPlatform(vlc_vk_t *vk)
{
    if (vk->window->type != VOUT_WINDOW_TYPE_HWND)
        return VLC_EGENERIC;

    return VLC_SUCCESS;
}
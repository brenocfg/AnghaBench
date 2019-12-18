#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  surface; TYPE_3__* window; TYPE_1__* instance; } ;
typedef  TYPE_4__ vlc_vk_t ;
struct TYPE_13__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hinstance; int /*<<< orphan*/  sType; } ;
typedef  TYPE_5__ VkWin32SurfaceCreateInfoKHR ;
typedef  scalar_t__ VkResult ;
typedef  int /*<<< orphan*/  VkInstance ;
struct TYPE_10__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_11__ {TYPE_2__ handle; } ;
struct TYPE_9__ {int /*<<< orphan*/  instance; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR ; 
 scalar_t__ VK_SUCCESS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 scalar_t__ vkCreateWin32SurfaceKHR (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vlc_vk_CreateSurface(vlc_vk_t *vk)
{
    VkInstance vkinst = vk->instance->instance;

    // Get current win32 HINSTANCE
    HINSTANCE hInst = GetModuleHandle(NULL);

    VkWin32SurfaceCreateInfoKHR winfo = {
         .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
         .hinstance = hInst,
         .hwnd = (HWND) vk->window->handle.hwnd,
    };

    VkResult res = vkCreateWin32SurfaceKHR(vkinst, &winfo, NULL, &vk->surface);
    if (res != VK_SUCCESS) {
        msg_Err(vk, "Failed creating Win32 surface");
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}
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
typedef  size_t WPARAM ;

/* Variables and functions */
 size_t SPY_MAX_VKKEYSNUM ; 
 char** VK_KeyNames ; 

const char *SPY_GetVKeyName(WPARAM wParam)
{
    const char *vk_key_name;

    if(wParam <= SPY_MAX_VKKEYSNUM && VK_KeyNames[wParam])
        vk_key_name = VK_KeyNames[wParam];
    else
        vk_key_name = "VK_???";

    return vk_key_name;
}
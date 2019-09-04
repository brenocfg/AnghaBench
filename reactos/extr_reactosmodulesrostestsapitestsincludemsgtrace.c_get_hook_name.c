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
typedef  int UINT ;

/* Variables and functions */
#define  WH_KEYBOARD 131 
#define  WH_KEYBOARD_LL 130 
#define  WH_MOUSE 129 
#define  WH_MOUSE_LL 128 

__attribute__((used)) static char* get_hook_name(UINT id)
{
    switch (id)
    {
        case WH_KEYBOARD: return "WH_KEYBOARD";
        case WH_KEYBOARD_LL: return "WH_KEYBOARD_LL";
        case WH_MOUSE: return "WH_MOUSE";
        case WH_MOUSE_LL: return "WH_MOUSE_LL";
        default: return NULL;
    }
}
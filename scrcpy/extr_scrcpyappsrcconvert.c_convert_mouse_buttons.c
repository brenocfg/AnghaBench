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
typedef  int uint32_t ;
typedef  enum android_motionevent_buttons { ____Placeholder_android_motionevent_buttons } android_motionevent_buttons ;

/* Variables and functions */
 int AMOTION_EVENT_BUTTON_BACK ; 
 int AMOTION_EVENT_BUTTON_FORWARD ; 
 int AMOTION_EVENT_BUTTON_PRIMARY ; 
 int AMOTION_EVENT_BUTTON_SECONDARY ; 
 int AMOTION_EVENT_BUTTON_TERTIARY ; 
 int SDL_BUTTON_LMASK ; 
 int SDL_BUTTON_MMASK ; 
 int SDL_BUTTON_RMASK ; 
 int SDL_BUTTON_X1 ; 
 int SDL_BUTTON_X2 ; 

__attribute__((used)) static enum android_motionevent_buttons
convert_mouse_buttons(uint32_t state) {
    enum android_motionevent_buttons buttons = 0;
    if (state & SDL_BUTTON_LMASK) {
        buttons |= AMOTION_EVENT_BUTTON_PRIMARY;
    }
    if (state & SDL_BUTTON_RMASK) {
        buttons |= AMOTION_EVENT_BUTTON_SECONDARY;
    }
    if (state & SDL_BUTTON_MMASK) {
        buttons |= AMOTION_EVENT_BUTTON_TERTIARY;
    }
    if (state & SDL_BUTTON_X1) {
        buttons |= AMOTION_EVENT_BUTTON_BACK;
    }
    if (state & SDL_BUTTON_X2) {
        buttons |= AMOTION_EVENT_BUTTON_FORWARD;
    }
    return buttons;
}
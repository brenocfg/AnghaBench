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
typedef  enum android_motionevent_action { ____Placeholder_android_motionevent_action } android_motionevent_action ;
typedef  int SDL_EventType ;

/* Variables and functions */
 int /*<<< orphan*/  AMOTION_EVENT_ACTION_DOWN ; 
 int /*<<< orphan*/  AMOTION_EVENT_ACTION_UP ; 
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MOUSEBUTTONDOWN ; 
 int /*<<< orphan*/  SDL_MOUSEBUTTONUP ; 

__attribute__((used)) static bool
convert_mouse_action(SDL_EventType from, enum android_motionevent_action *to) {
    switch (from) {
        MAP(SDL_MOUSEBUTTONDOWN, AMOTION_EVENT_ACTION_DOWN);
        MAP(SDL_MOUSEBUTTONUP,   AMOTION_EVENT_ACTION_UP);
        FAIL;
    }
}
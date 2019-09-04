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
typedef  enum android_keyevent_action { ____Placeholder_android_keyevent_action } android_keyevent_action ;
typedef  int SDL_EventType ;

/* Variables and functions */
 int /*<<< orphan*/  AKEY_EVENT_ACTION_DOWN ; 
 int /*<<< orphan*/  AKEY_EVENT_ACTION_UP ; 
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  MAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_KEYDOWN ; 
 int /*<<< orphan*/  SDL_KEYUP ; 

__attribute__((used)) static bool
convert_keycode_action(SDL_EventType from, enum android_keyevent_action *to) {
    switch (from) {
        MAP(SDL_KEYDOWN, AKEY_EVENT_ACTION_DOWN);
        MAP(SDL_KEYUP,   AKEY_EVENT_ACTION_UP);
        FAIL;
    }
}
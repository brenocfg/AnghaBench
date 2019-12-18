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

/* Variables and functions */
 int /*<<< orphan*/  test_serialize_back_or_screen_on () ; 
 int /*<<< orphan*/  test_serialize_collapse_notification_panel () ; 
 int /*<<< orphan*/  test_serialize_expand_notification_panel () ; 
 int /*<<< orphan*/  test_serialize_get_clipboard () ; 
 int /*<<< orphan*/  test_serialize_inject_keycode () ; 
 int /*<<< orphan*/  test_serialize_inject_mouse_event () ; 
 int /*<<< orphan*/  test_serialize_inject_scroll_event () ; 
 int /*<<< orphan*/  test_serialize_inject_text () ; 
 int /*<<< orphan*/  test_serialize_inject_text_long () ; 
 int /*<<< orphan*/  test_serialize_set_clipboard () ; 
 int /*<<< orphan*/  test_serialize_set_screen_power_mode () ; 

int main(void) {
    test_serialize_inject_keycode();
    test_serialize_inject_text();
    test_serialize_inject_text_long();
    test_serialize_inject_mouse_event();
    test_serialize_inject_scroll_event();
    test_serialize_back_or_screen_on();
    test_serialize_expand_notification_panel();
    test_serialize_collapse_notification_panel();
    test_serialize_get_clipboard();
    test_serialize_set_clipboard();
    test_serialize_set_screen_power_mode();
    return 0;
}
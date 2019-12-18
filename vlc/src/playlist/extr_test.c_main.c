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
 int /*<<< orphan*/  test_append () ; 
 int /*<<< orphan*/  test_callbacks_on_add_listener () ; 
 int /*<<< orphan*/  test_clear () ; 
 int /*<<< orphan*/  test_expand_item () ; 
 int /*<<< orphan*/  test_goto () ; 
 int /*<<< orphan*/  test_index_of () ; 
 int /*<<< orphan*/  test_insert () ; 
 int /*<<< orphan*/  test_items_added_callbacks () ; 
 int /*<<< orphan*/  test_items_moved_callbacks () ; 
 int /*<<< orphan*/  test_items_removed_callbacks () ; 
 int /*<<< orphan*/  test_items_reset_callbacks () ; 
 int /*<<< orphan*/  test_move () ; 
 int /*<<< orphan*/  test_next () ; 
 int /*<<< orphan*/  test_playback_order_changed_callbacks () ; 
 int /*<<< orphan*/  test_playback_repeat_changed_callbacks () ; 
 int /*<<< orphan*/  test_prev () ; 
 int /*<<< orphan*/  test_random () ; 
 int /*<<< orphan*/  test_remove () ; 
 int /*<<< orphan*/  test_request_goto_adapt () ; 
 int /*<<< orphan*/  test_request_goto_with_matching_hint () ; 
 int /*<<< orphan*/  test_request_goto_without_hint () ; 
 int /*<<< orphan*/  test_request_insert () ; 
 int /*<<< orphan*/  test_request_move_adapt () ; 
 int /*<<< orphan*/  test_request_move_to_end_adapt () ; 
 int /*<<< orphan*/  test_request_move_with_matching_hint () ; 
 int /*<<< orphan*/  test_request_move_without_hint () ; 
 int /*<<< orphan*/  test_request_remove_adapt () ; 
 int /*<<< orphan*/  test_request_remove_with_matching_hint () ; 
 int /*<<< orphan*/  test_request_remove_without_hint () ; 
 int /*<<< orphan*/  test_shuffle () ; 
 int /*<<< orphan*/  test_sort () ; 

int main(void)
{
    test_append();
    test_insert();
    test_move();
    test_remove();
    test_clear();
    test_expand_item();
    test_items_added_callbacks();
    test_items_moved_callbacks();
    test_items_removed_callbacks();
    test_items_reset_callbacks();
    test_playback_repeat_changed_callbacks();
    test_playback_order_changed_callbacks();
    test_callbacks_on_add_listener();
    test_index_of();
    test_prev();
    test_next();
    test_goto();
    test_request_insert();
    test_request_remove_with_matching_hint();
    test_request_remove_without_hint();
    test_request_remove_adapt();
    test_request_move_with_matching_hint();
    test_request_move_without_hint();
    test_request_move_adapt();
    test_request_move_to_end_adapt();
    test_request_goto_with_matching_hint();
    test_request_goto_without_hint();
    test_request_goto_adapt();
    test_random();
    test_shuffle();
    test_sort();
    return 0;
}
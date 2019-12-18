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
 int /*<<< orphan*/  test_vector_exp_growth () ; 
 int /*<<< orphan*/  test_vector_foreach () ; 
 int /*<<< orphan*/  test_vector_grow () ; 
 int /*<<< orphan*/  test_vector_index_of () ; 
 int /*<<< orphan*/  test_vector_insert_array () ; 
 int /*<<< orphan*/  test_vector_insert_remove () ; 
 int /*<<< orphan*/  test_vector_move () ; 
 int /*<<< orphan*/  test_vector_move_slice_backward () ; 
 int /*<<< orphan*/  test_vector_move_slice_forward () ; 
 int /*<<< orphan*/  test_vector_push_array () ; 
 int /*<<< orphan*/  test_vector_remove_slice () ; 
 int /*<<< orphan*/  test_vector_reserve () ; 
 int /*<<< orphan*/  test_vector_shrink_to_fit () ; 
 int /*<<< orphan*/  test_vector_swap_remove () ; 

int main(void) {
    test_vector_insert_remove();
    test_vector_push_array();
    test_vector_insert_array();
    test_vector_remove_slice();
    test_vector_swap_remove();
    test_vector_move();
    test_vector_move_slice_forward();
    test_vector_move_slice_backward();
    test_vector_index_of();
    test_vector_foreach();
    test_vector_grow();
    test_vector_exp_growth();
    test_vector_reserve();
    test_vector_shrink_to_fit();
    return 0;
}
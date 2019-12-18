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
 int /*<<< orphan*/  test_media_tree () ; 
 int /*<<< orphan*/  test_media_tree_callbacks () ; 
 int /*<<< orphan*/  test_media_tree_callbacks_on_add_listener () ; 

int main(void)
{
    test_media_tree();
    test_media_tree_callbacks();
    test_media_tree_callbacks_on_add_listener();
    return 0;
}
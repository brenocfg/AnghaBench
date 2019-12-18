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
 int /*<<< orphan*/  test_data_msg_encoding () ; 
 int /*<<< orphan*/  test_data_msg_get_param () ; 
 int /*<<< orphan*/  test_data_msg_open () ; 
 int /*<<< orphan*/  test_data_msg_update () ; 

__attribute__((used)) static void test_data_msg(void)
{
    test_data_msg_open();
    test_data_msg_update();
    test_data_msg_get_param();
    test_data_msg_encoding();
}
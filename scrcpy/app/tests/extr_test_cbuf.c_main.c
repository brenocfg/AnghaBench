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
 int /*<<< orphan*/  test_cbuf_empty () ; 
 int /*<<< orphan*/  test_cbuf_full () ; 
 int /*<<< orphan*/  test_cbuf_push_take () ; 

int main(void) {
    test_cbuf_empty();
    test_cbuf_full();
    test_cbuf_push_take();
    return 0;
}
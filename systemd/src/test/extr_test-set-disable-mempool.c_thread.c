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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 scalar_t__ NUM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  is_main_thread () ; 
 int /*<<< orphan*/ * set_free (int /*<<< orphan*/ *) ; 
 scalar_t__ set_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* thread(void *p) {
        Set **s = p;

        assert_se(s);
        assert_se(*s);

        assert_se(!is_main_thread());
        assert_se(set_size(*s) == NUM);
        *s = set_free(*s);

        return NULL;
}
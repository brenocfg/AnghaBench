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
 int /*<<< orphan*/  assert_se (int) ; 
 int signal_from_string (char const*) ; 
 char* strjoina (char*,char const*) ; 

__attribute__((used)) static void test_signal_from_string_one(const char *s, int val) {
        const char *p;

        assert_se(signal_from_string(s) == val);

        p = strjoina("SIG", s);
        assert_se(signal_from_string(p) == val);
}
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
 int /*<<< orphan*/  assert (int) ; 
 int strlen (char const*) ; 
 size_t utf8_truncation_index (char const*,int) ; 

__attribute__((used)) static void test_utf8_truncate(void) {
    const char *s = "aÉbÔc";
    assert(strlen(s) == 7); // É and Ô are 2 bytes-wide

    size_t count;

    count = utf8_truncation_index(s, 1);
    assert(count == 1);

    count = utf8_truncation_index(s, 2);
    assert(count == 1); // É is 2 bytes-wide

    count = utf8_truncation_index(s, 3);
    assert(count == 3);

    count = utf8_truncation_index(s, 4);
    assert(count == 4);

    count = utf8_truncation_index(s, 5);
    assert(count == 4); // Ô is 2 bytes-wide

    count = utf8_truncation_index(s, 6);
    assert(count == 6);

    count = utf8_truncation_index(s, 7);
    assert(count == 7);

    count = utf8_truncation_index(s, 8);
    assert(count == 7); // no more chars
}
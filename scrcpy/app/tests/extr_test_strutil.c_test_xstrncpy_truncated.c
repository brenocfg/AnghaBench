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
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 size_t xstrncpy (char*,char*,int) ; 

__attribute__((used)) static void test_xstrncpy_truncated(void) {
    char s[] = "xxx";
    size_t w = xstrncpy(s, "abcdef", sizeof(s));

    // returns 'n' (sizeof(s))
    assert(w == 4);

    // is nul-terminated
    assert(s[3] == '\0');

    // copies the content as expected
    assert(!strncmp("abcdef", s, 3));
}
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
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t xstrncpy (char*,char*,int) ; 

__attribute__((used)) static void test_xstrncpy_just_fit(void) {
    char s[] = "xxxxxx";
    size_t w = xstrncpy(s, "abcdef", sizeof(s));

    // returns strlen of copied string
    assert(w == 6);

    // is nul-terminated
    assert(s[6] == '\0');

    // copies the content as expected
    assert(!strcmp("abcdef", s));
}
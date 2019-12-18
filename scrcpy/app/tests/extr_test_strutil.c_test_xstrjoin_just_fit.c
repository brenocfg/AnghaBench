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
 size_t xstrjoin (char*,char const* const*,char,int) ; 

__attribute__((used)) static void test_xstrjoin_just_fit(void) {
    const char *const tokens[] = { "abc", "de", "fghi", NULL };
    char s[] = "xxxxxxxxxxx";
    size_t w = xstrjoin(s, tokens, ' ', sizeof(s));

    // returns strlen of concatenation
    assert(w == 11);

    // is nul-terminated
    assert(s[11] == '\0');

    // copies the content as expected
    assert(!strcmp("abc de fghi", s));
}
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
 int /*<<< orphan*/  STRLEN (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int base64mem (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int streq (char*,char*) ; 

__attribute__((used)) static void test_base64mem(void) {
        char *b64;

        assert_se(base64mem("", STRLEN(""), &b64) == 0);
        assert_se(streq(b64, ""));
        free(b64);

        assert_se(base64mem("f", STRLEN("f"), &b64) == 4);
        assert_se(streq(b64, "Zg=="));
        free(b64);

        assert_se(base64mem("fo", STRLEN("fo"), &b64) == 4);
        assert_se(streq(b64, "Zm8="));
        free(b64);

        assert_se(base64mem("foo", STRLEN("foo"), &b64) == 4);
        assert_se(streq(b64, "Zm9v"));
        free(b64);

        assert_se(base64mem("foob", STRLEN("foob"), &b64) == 8);
        assert_se(streq(b64, "Zm9vYg=="));
        free(b64);

        assert_se(base64mem("fooba", STRLEN("fooba"), &b64) == 8);
        assert_se(streq(b64, "Zm9vYmE="));
        free(b64);

        assert_se(base64mem("foobar", STRLEN("foobar"), &b64) == 8);
        assert_se(streq(b64, "Zm9vYmFy"));
        free(b64);
}
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
 int /*<<< orphan*/  assert_se (char*) ; 
 char* base32hexmem (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* streq (char*,char*) ; 

__attribute__((used)) static void test_base32hexmem(void) {
        char *b32;

        b32 = base32hexmem("", STRLEN(""), true);
        assert_se(b32);
        assert_se(streq(b32, ""));
        free(b32);

        b32 = base32hexmem("f", STRLEN("f"), true);
        assert_se(b32);
        assert_se(streq(b32, "CO======"));
        free(b32);

        b32 = base32hexmem("fo", STRLEN("fo"), true);
        assert_se(b32);
        assert_se(streq(b32, "CPNG===="));
        free(b32);

        b32 = base32hexmem("foo", STRLEN("foo"), true);
        assert_se(b32);
        assert_se(streq(b32, "CPNMU==="));
        free(b32);

        b32 = base32hexmem("foob", STRLEN("foob"), true);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOG="));
        free(b32);

        b32 = base32hexmem("fooba", STRLEN("fooba"), true);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOJ1"));
        free(b32);

        b32 = base32hexmem("foobar", STRLEN("foobar"), true);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOJ1E8======"));
        free(b32);

        b32 = base32hexmem("", STRLEN(""), false);
        assert_se(b32);
        assert_se(streq(b32, ""));
        free(b32);

        b32 = base32hexmem("f", STRLEN("f"), false);
        assert_se(b32);
        assert_se(streq(b32, "CO"));
        free(b32);

        b32 = base32hexmem("fo", STRLEN("fo"), false);
        assert_se(b32);
        assert_se(streq(b32, "CPNG"));
        free(b32);

        b32 = base32hexmem("foo", STRLEN("foo"), false);
        assert_se(b32);
        assert_se(streq(b32, "CPNMU"));
        free(b32);

        b32 = base32hexmem("foob", STRLEN("foob"), false);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOG"));
        free(b32);

        b32 = base32hexmem("fooba", STRLEN("fooba"), false);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOJ1"));
        free(b32);

        b32 = base32hexmem("foobar", STRLEN("foobar"), false);
        assert_se(b32);
        assert_se(streq(b32, "CPNMUOJ1E8"));
        free(b32);
}
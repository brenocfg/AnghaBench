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
 int /*<<< orphan*/  EXTRACT_UNQUOTE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int extract_many_words (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int isempty (char const*) ; 
 int streq_ptr (char*,char*) ; 

__attribute__((used)) static void test_extract_many_words(void) {
        const char *p, *original;
        char *a, *b, *c;

        p = original = "foobar waldi piep";
        assert_se(extract_many_words(&p, NULL, 0, &a, &b, &c, NULL) == 3);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, "foobar"));
        assert_se(streq_ptr(b, "waldi"));
        assert_se(streq_ptr(c, "piep"));
        free(a);
        free(b);
        free(c);

        p = original = "'foobar' wa\"ld\"i   ";
        assert_se(extract_many_words(&p, NULL, 0, &a, &b, &c, NULL) == 2);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, "'foobar'"));
        assert_se(streq_ptr(b, "wa\"ld\"i"));
        assert_se(streq_ptr(c, NULL));
        free(a);
        free(b);

        p = original = "'foobar' wa\"ld\"i   ";
        assert_se(extract_many_words(&p, NULL, EXTRACT_UNQUOTE, &a, &b, &c, NULL) == 2);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, "foobar"));
        assert_se(streq_ptr(b, "waldi"));
        assert_se(streq_ptr(c, NULL));
        free(a);
        free(b);

        p = original = "";
        assert_se(extract_many_words(&p, NULL, 0, &a, &b, &c, NULL) == 0);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, NULL));
        assert_se(streq_ptr(b, NULL));
        assert_se(streq_ptr(c, NULL));

        p = original = "  ";
        assert_se(extract_many_words(&p, NULL, 0, &a, &b, &c, NULL) == 0);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, NULL));
        assert_se(streq_ptr(b, NULL));
        assert_se(streq_ptr(c, NULL));

        p = original = "foobar";
        assert_se(extract_many_words(&p, NULL, 0, NULL) == 0);
        assert_se(p == original);

        p = original = "foobar waldi";
        assert_se(extract_many_words(&p, NULL, 0, &a, NULL) == 1);
        assert_se(p == original+7);
        assert_se(streq_ptr(a, "foobar"));
        free(a);

        p = original = "     foobar    ";
        assert_se(extract_many_words(&p, NULL, 0, &a, NULL) == 1);
        assert_se(isempty(p));
        assert_se(streq_ptr(a, "foobar"));
        free(a);
}
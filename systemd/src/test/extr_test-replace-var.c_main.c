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
 int /*<<< orphan*/  assert_se (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lookup ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* replace_var (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* streq (char*,char*) ; 
 char* strreplace (char*,char*,char*) ; 

int main(int argc, char *argv[]) {
        char *r;

        assert_se(r = replace_var("@@@foobar@xyz@HALLO@foobar@test@@testtest@TEST@...@@@", lookup, NULL));
        puts(r);
        assert_se(streq(r, "@@@foobar@xyz<<<HALLO>>>foobar@test@@testtest<<<TEST>>>...@@@"));
        free(r);

        assert_se(r = strreplace("XYZFFFFXYZFFFFXYZ", "XYZ", "ABC"));
        puts(r);
        assert_se(streq(r, "ABCFFFFABCFFFFABC"));
        free(r);

        return 0;
}
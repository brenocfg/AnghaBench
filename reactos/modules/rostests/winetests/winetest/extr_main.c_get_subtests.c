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
struct wine_test {int subtest_count; char* name; int /*<<< orphan*/ * subtests; int /*<<< orphan*/  exename; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  R_ERROR ; 
 int /*<<< orphan*/  R_FATAL ; 
 int /*<<< orphan*/  R_WARNING ; 
 int errno ; 
 int /*<<< orphan*/  extract_test (struct wine_test*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ remove (char*) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  run_ex (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strmake (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 char* strstr (char*,char const*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 char* tempnam (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  whitespace ; 
 int /*<<< orphan*/ * xmalloc (int) ; 
 void* xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
get_subtests (const char *tempdir, struct wine_test *test, LPTSTR res_name)
{
    char *subname, *cmd;
    FILE *subfile;
    size_t total;
    char buffer[8192], *index;
    static const char header[] = "Valid test names:";
    int allocated;

    test->subtest_count = 0;

    subname = tempnam (0, "sub");
    if (!subname) report (R_FATAL, "Can't name subtests file.");

    extract_test (test, tempdir, res_name);
    cmd = strmake (NULL, "%s --list", test->exename);
    run_ex (cmd, subname, tempdir, 5000);
    free (cmd);

    subfile = fopen (subname, "r");
    if (!subfile) {
        report (R_ERROR, "Can't open subtests output of %s: %d",
                test->name, errno);
        goto quit;
    }
    total = fread (buffer, 1, sizeof buffer, subfile);
    fclose (subfile);
    if (sizeof buffer == total) {
        report (R_ERROR, "Subtest list of %s too big.",
                test->name, sizeof buffer);
        goto quit;
    }
    buffer[total] = 0;

    index = strstr (buffer, header);
    if (!index) {
        report (R_ERROR, "Can't parse subtests output of %s",
                test->name);
        goto quit;
    }
    index += sizeof header;

    allocated = 10;
    test->subtests = xmalloc (allocated * sizeof(char*));
    index = strtok (index, whitespace);
    while (index) {
        if (test->subtest_count == allocated) {
            allocated *= 2;
            test->subtests = xrealloc (test->subtests,
                                       allocated * sizeof(char*));
        }
        test->subtests[test->subtest_count++] = strdup (index);
        index = strtok (NULL, whitespace);
    }
    test->subtests = xrealloc (test->subtests,
                               test->subtest_count * sizeof(char*));

 quit:
    if (remove (subname))
        report (R_WARNING, "Can't delete file '%s': %d",
                subname, errno);
    free (subname);
}
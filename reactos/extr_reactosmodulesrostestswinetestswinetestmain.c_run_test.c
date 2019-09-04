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
struct wine_test {int /*<<< orphan*/  name; int /*<<< orphan*/  exename; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* get_file_rev (char const*) ; 
 char* get_test_source_file (int /*<<< orphan*/ ,char const*) ; 
 int run_ex (char*,int /*<<< orphan*/ *,char const*,int) ; 
 char* strmake (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static void
run_test (struct wine_test* test, const char* subtest, const char *tempdir)
{
    int status;
    const char* file = get_test_source_file(test->name, subtest);
    const char* rev = get_file_rev(file);
    char *cmd = strmake (NULL, "%s %s", test->exename, subtest);

    xprintf ("%s:%s start %s %s\n", test->name, subtest, file, rev);
    status = run_ex (cmd, NULL, tempdir, 120000);
    free (cmd);
    xprintf ("%s:%s done (%d)\n", test->name, subtest, status);
}
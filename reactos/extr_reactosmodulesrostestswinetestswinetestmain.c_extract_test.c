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
struct wine_test {char* name; char* exename; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  R_FATAL ; 
 int /*<<< orphan*/  R_STEP ; 
 int /*<<< orphan*/  TESTRES ; 
 int /*<<< orphan*/ * extract_rcdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* strmake (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testexe ; 
 char* xrealloc (char*,int) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
extract_test (struct wine_test *test, const char *dir, LPTSTR res_name)
{
    BYTE* code;
    DWORD size;
    FILE* fout;
    char *exepos;

    code = extract_rcdata (res_name, TESTRES, &size);
    if (!code) report (R_FATAL, "Can't find test resource %s: %d",
                       res_name, GetLastError ());
    test->name = xstrdup( res_name );
    test->exename = strmake (NULL, "%s/%s", dir, test->name);
    exepos = strstr (test->name, testexe);
    if (!exepos) report (R_FATAL, "Not an .exe file: %s", test->name);
    *exepos = 0;
    test->name = xrealloc (test->name, exepos - test->name + 1);
    report (R_STEP, "Extracting: %s", test->name);

    if (!(fout = fopen (test->exename, "wb")) ||
        (fwrite (code, size, 1, fout) != 1) ||
        fclose (fout)) report (R_FATAL, "Failed to write file %s.",
                               test->exename);
}
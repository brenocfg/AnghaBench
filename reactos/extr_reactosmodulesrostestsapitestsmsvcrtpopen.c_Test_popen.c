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
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 int* _errno () ; 
 int _pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _popen (char*,char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lstrcmp (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void Test_popen()
{
    FILE * f;
    int r;
    char str[20];

    /* NOTE: We suppose that the NT test installation has an accessible cmd.exe */
    f = _popen("cmd.exe /C \"echo Hallo\"", "r");
    ok(f != NULL, "_popen returns NULL!\n");

    ZeroMemory(str, sizeof(str));
    fgets(str, sizeof(str) - 1, f);
    ok(lstrcmp(str, "Hallo\n") == 0, "fgets: expected \"Hallo\", got %s.\n", str);

    r = _pclose(f);
    ok(r == 0, "_pclose: expected 0, got %i.\n", r);
    r = *_errno();
    ok(r == 0, "_errno: expected 0, got %i,\n", r);
}
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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ENVVAR_NOT_FOUND ; 
 int ExpandEnvironmentStringsA (char*,char*,int) ; 
 scalar_t__ GetLastError () ; 
 int GetWindowsDirectoryA (char*,int) ; 
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char const*) ; 
 int /*<<< orphan*/  lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_ExpandEnvironmentStringsA(void)
{
    const char* value="Long long value";
    const char* not_an_env_var="%NotAnEnvVar%";
    char buf[256], buf1[256], buf2[0x8000];
    DWORD ret_size, ret_size1;

    SetEnvironmentVariableA("EnvVar", value);

    ret_size = ExpandEnvironmentStringsA(NULL, buf1, sizeof(buf1));
    ok(ret_size == 1 || ret_size == 0 /* Win9x */ || ret_size == 2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d\n", ret_size);

    /* Try to get the required buffer size 'the natural way' */
    strcpy(buf, "%EnvVar%");
    ret_size = ExpandEnvironmentStringsA(buf, NULL, 0);
    ok(ret_size == strlen(value)+1 || /* win98 */
       ret_size == (strlen(value)+1)*2 || /* NT4 */
       ret_size == strlen(value)+2 || /* win2k, XP, win2k3 */
       ret_size == 0 /* Win95 */,
       "ExpandEnvironmentStrings returned %d instead of %d, %d or %d\n",
       ret_size, lstrlenA(value)+1, lstrlenA(value)+2, 0);

    /* Again, side-stepping the Win95 bug */
    ret_size = ExpandEnvironmentStringsA(buf, buf1, 0);
    /* v5.1.2600.2945 (XP SP2) returns len + 2 here! */
    ok(ret_size == strlen(value)+1 || ret_size == strlen(value)+2 ||
       ret_size == (strlen(value)+1)*2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d instead of %d\n",
       ret_size, lstrlenA(value)+1);

    /* Try with a buffer that's too small */
    ret_size = ExpandEnvironmentStringsA(buf, buf1, 12);
    /* v5.1.2600.2945 (XP SP2) returns len + 2 here! */
    ok(ret_size == strlen(value)+1 || ret_size == strlen(value)+2 ||
       ret_size == (strlen(value)+1)*2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d instead of %d\n",
       ret_size, lstrlenA(value)+1);

    /* Try with a buffer of just the right size */
    /* v5.1.2600.2945 (XP SP2) needs and returns len + 2 here! */
    ret_size = ExpandEnvironmentStringsA(buf, buf1, ret_size);
    ok(ret_size == strlen(value)+1 || ret_size == strlen(value)+2 ||
       ret_size == (strlen(value)+1)*2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d instead of %d\n",
       ret_size, lstrlenA(value)+1);
    ok(!strcmp(buf1, value), "ExpandEnvironmentStrings returned [%s]\n", buf1);

    /* Try with an unset environment variable */
    strcpy(buf, not_an_env_var);
    ret_size = ExpandEnvironmentStringsA(buf, buf1, sizeof(buf1));
    ok(ret_size == strlen(not_an_env_var)+1 ||
       ret_size == (strlen(not_an_env_var)+1)*2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d instead of %d\n", ret_size, lstrlenA(not_an_env_var)+1);
    ok(!strcmp(buf1, not_an_env_var), "ExpandEnvironmentStrings returned [%s]\n", buf1);

    /* test a large destination size */
    strcpy(buf, "12345");
    ret_size = ExpandEnvironmentStringsA(buf, buf2, sizeof(buf2));
    ok(!strcmp(buf, buf2), "ExpandEnvironmentStrings failed %s vs %s. ret_size = %d\n", buf, buf2, ret_size);

    ret_size1 = GetWindowsDirectoryA(buf1,256);
    ok ((ret_size1 >0) && (ret_size1<256), "GetWindowsDirectory Failed\n");
    ret_size = ExpandEnvironmentStringsA("%SystemRoot%",buf,sizeof(buf));
    if (ERROR_ENVVAR_NOT_FOUND != GetLastError())
    {
        ok(!strcmp(buf, buf1), "ExpandEnvironmentStrings failed %s vs %s. ret_size = %d\n", buf, buf1, ret_size);
    }

    /* Try with a variable that references another */
    SetEnvironmentVariableA("IndirectVar", "Foo%EnvVar%Bar");
    strcpy(buf, "Indirect-%IndirectVar%-Indirect");
    strcpy(buf2, "Indirect-Foo%EnvVar%Bar-Indirect");
    ret_size = ExpandEnvironmentStringsA(buf, buf1, sizeof(buf1));
    ok(ret_size == strlen(buf2)+1 ||
       ret_size == (strlen(buf2)+1)*2 /* NT4 */,
       "ExpandEnvironmentStrings returned %d instead of %d\n", ret_size, lstrlenA(buf2)+1);
    ok(!strcmp(buf1, buf2), "ExpandEnvironmentStrings returned [%s]\n", buf1);
    SetEnvironmentVariableA("IndirectVar", NULL);

    SetEnvironmentVariableA("EnvVar", NULL);
}
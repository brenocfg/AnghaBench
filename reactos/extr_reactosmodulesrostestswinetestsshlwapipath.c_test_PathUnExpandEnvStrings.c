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
typedef  int /*<<< orphan*/  sysrootW ;
typedef  int /*<<< orphan*/  sysrootA ;
typedef  int /*<<< orphan*/  envvarA ;
typedef  int /*<<< orphan*/  buff ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int GetEnvironmentVariableA (char*,char*,int) ; 
 int GetEnvironmentVariableW (char const*,char*,int) ; 
 int GetLastError () ; 
 scalar_t__ GetSystemDirectoryA (char*,int) ; 
 scalar_t__ GetSystemDirectoryW (char*,int) ; 
 int MAX_PATH ; 
 int SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pPathUnExpandEnvStringsA (char*,char*,int) ; 
 int pPathUnExpandEnvStringsW (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_PathUnExpandEnvStrings(void)
{
    static const WCHAR sysrootW[] = {'%','S','y','s','t','e','m','R','o','o','t','%',0};
    static const WCHAR sysdriveW[] = {'%','S','y','s','t','e','m','D','r','i','v','e','%',0};
    static const WCHAR nonpathW[] = {'p','a','t','h',0};
    static const WCHAR computernameW[] = {'C','O','M','P','U','T','E','R','N','A','M','E',0};
    static const char sysrootA[] = "%SystemRoot%";
    static const char sysdriveA[] = "%SystemDrive%";
    WCHAR pathW[MAX_PATH], buffW[MAX_PATH], sysdrvW[3], envvarW[30];
    char path[MAX_PATH], buff[MAX_PATH], sysdrvA[3], envvarA[30];
    BOOL ret;
    UINT len;

    if (!pPathUnExpandEnvStringsA || !pPathUnExpandEnvStringsW)
    {
        win_skip("PathUnExpandEnvStrings not available\n");
        return;
    }

    /* The value of ComputerName is not a path */
    ret = GetEnvironmentVariableA("COMPUTERNAME", envvarA, sizeof(envvarA));
    ok(ret, "got %d\n", ret);
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsA(envvarA, buff, sizeof(buff));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());

    ret = GetEnvironmentVariableW(computernameW, envvarW, ARRAY_SIZE(envvarW));
    ok(ret, "got %d\n", ret);
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsW(envvarW, buffW, ARRAY_SIZE(buffW));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());

    /* something that can't be represented with env var */
    strcpy(path, "somepath_name");
    strcpy(buff, "xx");
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsA(path, buff, sizeof(buff));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());
    ok(buff[0] == 'x', "wrong return string %s\n", buff);

    len = GetSystemDirectoryA(path, MAX_PATH);
    ok(len > 0, "failed to get sysdir\n");

    sysdrvA[0] = path[0];
    strcpy(&sysdrvA[1], ":");

    /* buffer size is not enough */
    strcpy(buff, "xx");
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsA(path, buff, 5);
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d\n", ret);
    ok(buff[0] == 'x', "wrong return string %s\n", buff);

    /* buffer size is enough to hold variable name only */
    strcpy(buff, "xx");
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsA(path, buff, sizeof(sysrootA));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());
    ok(buff[0] == 'x', "wrong return string %s\n", buff);

    /* enough size */
    buff[0] = 0;
    ret = pPathUnExpandEnvStringsA(path, buff, sizeof(buff));
    ok(ret, "got %d\n", ret);
    ok(!strncmp(buff, sysrootA, sizeof(sysrootA)-1), "wrong return string %s\n", buff);

    /* expanded value occurs multiple times */
    /* for drive C: it unexpands it like 'C:C:' -> '%SystemDrive%C:' */
    buff[0] = 0;
    strcpy(path, sysdrvA);
    strcat(path, sysdrvA);
    ret = pPathUnExpandEnvStringsA(path, buff, sizeof(buff));
    ok(ret, "got %d\n", ret);
    /* expected string */
    strcpy(path, sysdriveA);
    strcat(path, sysdrvA);
    ok(!strcmp(buff, path), "wrong unexpanded string %s, expected %s\n", buff, path);

    /* now with altered variable */
    ret = GetEnvironmentVariableA("SystemDrive", envvarA, sizeof(envvarA));
    ok(ret, "got %d\n", ret);

    ret = SetEnvironmentVariableA("SystemDrive", "WW");
    ok(ret, "got %d\n", ret);

    /* variables are not cached */
    strcpy(path, sysdrvA);
    strcat(path, sysdrvA);
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsA(path, buff, sizeof(buff));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());

    ret = SetEnvironmentVariableA("SystemDrive", envvarA);
    ok(ret, "got %d\n", ret);

    /* PathUnExpandEnvStringsW */

    /* something that can't be represented with env var */
    lstrcpyW(pathW, nonpathW);
    buffW[0] = 'x'; buffW[1] = 0;
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsW(pathW, buffW, ARRAY_SIZE(buffW));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());
    ok(buffW[0] == 'x', "wrong return string %s\n", wine_dbgstr_w(buffW));

    len = GetSystemDirectoryW(pathW, MAX_PATH);
    ok(len > 0, "failed to get sysdir\n");

    sysdrvW[0] = pathW[0];
    sysdrvW[1] = ':';
    sysdrvW[2] = 0;

    /* buffer size is not enough */
    buffW[0] = 'x'; buffW[1] = 0;
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsW(pathW, buffW, 5);
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());
    ok(buffW[0] == 'x', "wrong return string %s\n", wine_dbgstr_w(buffW));

    /* buffer size is enough to hold variable name only */
    buffW[0] = 'x'; buffW[1] = 0;
    SetLastError(0xdeadbeef);
    ret = pPathUnExpandEnvStringsW(pathW, buffW, ARRAY_SIZE(sysrootW));
    ok(!ret && GetLastError() == 0xdeadbeef, "got %d, error %d\n", ret, GetLastError());
    ok(buffW[0] == 'x', "wrong return string %s\n", wine_dbgstr_w(buffW));

    /* enough size */
    buffW[0] = 0;
    ret = pPathUnExpandEnvStringsW(pathW, buffW, ARRAY_SIZE(buffW));
    ok(ret, "got %d\n", ret);
    ok(!memcmp(buffW, sysrootW, sizeof(sysrootW) - sizeof(WCHAR)), "wrong return string %s\n", wine_dbgstr_w(buffW));

    /* expanded value occurs multiple times */
    /* for drive C: it unexpands it like 'C:C:' -> '%SystemDrive%C:' */
    buffW[0] = 0;
    lstrcpyW(pathW, sysdrvW);
    lstrcatW(pathW, sysdrvW);
    ret = pPathUnExpandEnvStringsW(pathW, buffW, ARRAY_SIZE(buffW));
    ok(ret, "got %d\n", ret);
    /* expected string */
    lstrcpyW(pathW, sysdriveW);
    lstrcatW(pathW, sysdrvW);
    ok(!lstrcmpW(buffW, pathW), "wrong unexpanded string %s, expected %s\n", wine_dbgstr_w(buffW), wine_dbgstr_w(pathW));
}
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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  Env ;
typedef  int /*<<< orphan*/  Data ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetEnvironmentVariableA (char*,char*,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 int pGetUserProfileDirectoryA (int /*<<< orphan*/ ,char*,int*) ; 
 int pOpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_Predefined(void)
{
    char Data[1024];
    DWORD DataSize;
    char Env[sizeof(Data)];
    DWORD EnvSize;
    HANDLE Token;
    BOOL NoErr;

    /*
     * Check value of %USERPROFILE%, should be same as GetUserProfileDirectory()
     * If this fails, your test environment is probably not set up
     */
    if (pOpenProcessToken == NULL || pGetUserProfileDirectoryA == NULL)
    {
        skip("Skipping USERPROFILE check\n");
        return;
    }
    NoErr = pOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &Token);
    ok(NoErr, "Failed to open token, error %u\n", GetLastError());
    DataSize = sizeof(Data);
    NoErr = pGetUserProfileDirectoryA(Token, Data, &DataSize);
    ok(NoErr, "Failed to get user profile dir, error %u\n", GetLastError());
    if (NoErr)
    {
        EnvSize = GetEnvironmentVariableA("USERPROFILE", Env, sizeof(Env));
        ok(EnvSize != 0 && EnvSize <= sizeof(Env),
           "Failed to retrieve environment variable USERPROFILE, error %u\n",
           GetLastError());
        ok(strcmp(Data, Env) == 0,
           "USERPROFILE env var %s doesn't match GetUserProfileDirectory %s\n",
           Env, Data);
    }
    else
        skip("Skipping USERPROFILE check, can't get user profile dir\n");
    NoErr = CloseHandle(Token);
    ok(NoErr, "Failed to close token, error %u\n", GetLastError());
}
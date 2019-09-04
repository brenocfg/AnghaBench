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
typedef  int /*<<< orphan*/  volume ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_NAME ; 
 int ERROR_MORE_DATA ; 
 int GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetVolumeNameForVolumeMountPointA (char*,char*,int) ; 
 int /*<<< orphan*/  pGetVolumePathNamesForVolumeNameA (char*,char*,int,int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetVolumePathNamesForVolumeNameA(void)
{
    BOOL ret;
    char volume[MAX_PATH], buffer[MAX_PATH];
    DWORD len, error;

    if (!pGetVolumePathNamesForVolumeNameA || !pGetVolumeNameForVolumeMountPointA)
    {
        win_skip("required functions not found\n");
        return;
    }

    ret = pGetVolumeNameForVolumeMountPointA( "c:\\", volume, sizeof(volume) );
    ok(ret, "failed to get volume name %u\n", GetLastError());
    trace("c:\\ -> %s\n", volume);

    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( NULL, NULL, 0, NULL );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( "", NULL, 0, NULL );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( volume, NULL, 0, NULL );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_MORE_DATA, "expected ERROR_MORE_DATA got %u\n", error);

    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( volume, buffer, 0, NULL );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_MORE_DATA, "expected ERROR_MORE_DATA got %u\n", error);

    memset( buffer, 0xff, sizeof(buffer) );
    ret = pGetVolumePathNamesForVolumeNameA( volume, buffer, sizeof(buffer), NULL );
    ok(ret, "failed to get path names %u\n", GetLastError());
    ok(!strcmp( "C:\\", buffer ), "expected \"\\C:\" got \"%s\"\n", buffer);
    ok(!buffer[4], "expected double null-terminated buffer\n");

    len = 0;
    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( NULL, NULL, 0, &len );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    len = 0;
    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( NULL, NULL, sizeof(buffer), &len );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    len = 0;
    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( NULL, buffer, sizeof(buffer), &len );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    len = 0;
    SetLastError( 0xdeadbeef );
    ret = pGetVolumePathNamesForVolumeNameA( NULL, buffer, sizeof(buffer), &len );
    error = GetLastError();
    ok(!ret, "expected failure\n");
    ok(error == ERROR_INVALID_NAME, "expected ERROR_INVALID_NAME got %u\n", error);

    len = 0;
    memset( buffer, 0xff, sizeof(buffer) );
    ret = pGetVolumePathNamesForVolumeNameA( volume, buffer, sizeof(buffer), &len );
    ok(ret, "failed to get path names %u\n", GetLastError());
    ok(len == 5 || broken(len == 2), "expected 5 got %u\n", len);
    ok(!strcmp( "C:\\", buffer ), "expected \"\\C:\" got \"%s\"\n", buffer);
    ok(!buffer[4], "expected double null-terminated buffer\n");
}
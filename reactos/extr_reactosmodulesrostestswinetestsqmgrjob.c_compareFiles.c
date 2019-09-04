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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int ReadFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void compareFiles(WCHAR *n1, WCHAR *n2)
{
    char b1[256];
    char b2[256];
    DWORD s1, s2;
    HANDLE f1, f2;

    f1 = CreateFileW(n1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL, NULL);
    ok(f1 != INVALID_HANDLE_VALUE, "CreateFile\n");

    f2 = CreateFileW(n2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL, NULL);
    ok(f2 != INVALID_HANDLE_VALUE, "CreateFile\n");

    /* Neither of these files is very big */
    ok(ReadFile(f1, b1, sizeof b1, &s1, NULL), "ReadFile\n");
    ok(ReadFile(f2, b2, sizeof b2, &s2, NULL), "ReadFile\n");

    CloseHandle(f1);
    CloseHandle(f2);

    ok(s1 == s2, "Files differ in length\n");
    ok(memcmp(b1, b2, s1) == 0, "Files differ in contents\n");
}
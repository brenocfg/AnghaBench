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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FR_PRIVATE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RemoveFontResourceExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID RemoveTempFont(LPWSTR TempFile)
{
    BOOL Success;
    Success = RemoveFontResourceExW(TempFile, FR_PRIVATE, 0);
    ok(Success, "RemoveFontResourceEx() failed, we're leaving fonts installed : %lu\n", GetLastError());
    DeleteFileW(TempFile);
}
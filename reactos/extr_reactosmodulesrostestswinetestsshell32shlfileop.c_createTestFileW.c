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

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void createTestFileW(const WCHAR *name)
{
    HANDLE file;

    file = CreateFileW(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    ok(file != INVALID_HANDLE_VALUE, "Failure to open file\n");
    CloseHandle(file);
}
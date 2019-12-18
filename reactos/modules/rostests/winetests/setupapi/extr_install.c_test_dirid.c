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

/* Variables and functions */
 int DIRID_NULL ; 
 int DIRID_SYSTEM ; 
 int DIRID_WINDOWS ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  check_dirid (int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void test_dirid(void)
{
    char expected[MAX_PATH];

    check_dirid(DIRID_NULL, "");

    GetWindowsDirectoryA(expected, MAX_PATH);
    check_dirid(DIRID_WINDOWS, expected);

    GetSystemDirectoryA(expected, MAX_PATH);
    check_dirid(DIRID_SYSTEM, expected);

    strcat(expected, "\\unknown");
    check_dirid(40, expected);
}